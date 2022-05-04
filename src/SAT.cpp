#include "SAT.hpp"

namespace pre
{
template <typename REAL>
void
SATPreSolver<REAL>::buildProblem( const std::string& inFileName )
{
   std::ifstream infile( inFileName );
   assert( !infile.fail() );
   this->inputIns = inFileName;
   this->instanceType = parser::opb_read_to_sat( infile, this->exprs );
   //    this->exprs.print();

   infile.close();
}

template <typename REAL>
void
SATPreSolver<REAL>::redundancyDetection()
{
   //* check every pair of constraint using roundingSat
   //* D implies C means D and neg C unsat, discard C then
   std::string rsStat;
   auto& es = this->exprs.getExprs();
   auto D = es.begin();
   auto C = es.begin();

   while( D != es.end() )
   {
      C = es.begin();
      while( C != es.end() )
      {
         if( C == D || ( C->getVarsSize() > this->redCmpSize &&
                         D->getVarsSize() > this->redCmpSize ) )
         {
            C++;
            continue;
         }
         std::string preInfo =
             "* #variable= " + aux::tos( this->exprs.getVarNum() ) +
             " #constraint= 2 \n" +
             aux::Expr2String( D->getCols(), D->getDeg() ) + '\n' +
             aux::Expr2NegString( C->getCols(), C->getDeg() );

         // std::cout << preInfo << std::endl
         //           << aux::Expr2String(C->getCols(), C->getDeg())
         //           << std::endl;

         rsStat =
             pre::runRoundingSat::runforRedundancy( preInfo, this->inputIns );

         auto tmp = C;
         tmp++;
         if( rsStat == "UNSATISFIABLE" )
         {
            this->redRelation.push_back( std::make_pair( *D, *C ) );
            es.erase( C );
            this->redDelNum++;
         }
         else
         {
            assert( rsStat == "SATISFIABLE" || rsStat == "OPTIMUM" );
         }
         C = tmp;
         this->redCallNum++;
      }
      D++;
   }

   // for (int i = 0; i < redRelation.size(); i++) {
   //     redRelation[i].first.print();
   //     std::cout << "|= ";
   //     redRelation[i].second.print();
   //     std::cout << "Neg: "
   //               << aux::Expr2NegString(redRelation[i].second.getCols(),
   //                                      redRelation[i].second.getDeg())
   //               << std::endl;
   //     std::cout << std::endl;
   // }

   return;
}

template <typename REAL>
void
SATPreSolver<REAL>::hyperBinaryResolution()
{
   auto buildGraph = [&]( auto& es, Graph<REAL>& g )
   {
      int N = g.getNodeNum();
      int u, v;
      std::vector<int> lits;
      bool flag = false;
      for( auto e : es )
      {
         if( e.getVarsSize() != 2 )
            continue;
         auto& cols = e.getCols();
         e.getLits( lits );
         assert( lits.size() == 2 );
         if( cols.at( lits[0] ) == 0 || cols.at( lits[1] ) == 0 )
            continue;
         if( (int)( cols.at( lits[0] ) > 0 ) * cols.at( lits[0] ) +
                 (int)( cols.at( lits[1] ) > 0 ) * cols.at( lits[1] ) <
             e.getDeg() ) //* maximum of LHS < RHS
         {
            this->presolveStatus = 2;
            this->solutionStatus = solStat::UNSATISFIABLE;
            break;
         }
         // normalize variable
         u = cols.at( lits[0] ) > 0 ? lits[0] : lits[0] + N;
         v = cols.at( lits[1] ) > 0 ? lits[1] : lits[1] + N;
         // TODO: define unsatisfiable binary constraint
         g.addEdge( u, v, e ); // add edge u+N -> v
         g.addEdge( v, u, e ); // add edge v+N -> u
         flag = true;
      }
      return flag;
   };
   auto resolveWithLit = [&]( Expr<REAL>& e1, Expr<REAL>& e2, const int& u,
                              const int& v ) { //* resolve on u and save v
      assert( e2.getVarsSize() == 2 );
      auto& col1 = e1.getCols();
      auto& col2 = e2.getCols();
      assert( col1.at( u ) != 0 && col2.at( u ) != 0 );
      REAL _lcm =
          aux::lcm( aux::abs( col1.at( u ) ), aux::abs( col2.at( u ) ) );
      assert( _lcm > 0 );
      REAL factor1 = _lcm / aux::abs( col1.at( u ) );
      REAL factor2 = _lcm / aux::abs( col2.at( u ) );
      assert( factor1 > 0 && factor2 > 0 );
      e1.delateCol( u );   // resolve u, remove it
      for( auto c : col1 ) // multiply the factor
      {
         e1.setCoeff( c.first, col1.at( c.first ) * factor1 );
      }
      if( col1.count( v ) )
         e1.setCoeff( v, col1.at( v ) + col2.at( v ) * factor2 );
      else
         e1.setCoeff( v, col2.at( v ) * factor2 );
      e1.setDeg( e1.getDeg() * factor1 + e2.getDeg() * factor2 );

      // divide gcd
      auto& newCol1 = e1.getCols();
      assert( newCol1.count( v ) );
      REAL _gcd = aux::abs( e1.getDeg() );
      if( _gcd == 1 ) // special handle for 1
         return;
      for( auto c : newCol1 )
      {
         assert( c.second != 0 || ( c.second == 0 && c.first == v ) );
         if( _gcd == 1 )
            break;
         if( c.second == 0 )
            continue;
         _gcd = aux::gcd( _gcd, aux::abs( c.second ) );
      }
      if( _gcd != 1 )
      {
         assert( _gcd > 1 );
         for( auto c : newCol1 )
         {
            assert( c.second % _gcd == 0 );
            e1.setCoeff( c.first, c.second / _gcd );
         }
         e1.setDeg( e1.getDeg() / _gcd );
      }

      return;
   };
   auto resolve = [&]( Graph<REAL>& g, Expr<REAL>& longExp, Expr<REAL>& ansExp,
                       const int& saveLit, int& v, int& gv )
   {
      std::vector<int> lits;
      auto& cols = longExp.getCols();
      longExp.getLits( lits );
      ansExp = longExp;

      int N = g.getNodeNum();
      int gu;
      msg.info( "saveLit {} common lit v {} Exp ", saveLit, v );
      longExp.print();

      //* u1 + u2 + ....
      //* u is the literal to be resolved
      //* gv is the common neighbor of u
      //* new constraint should only contains saveLit and v
      for( auto u : lits )
      {
         if( u == saveLit )
            continue;
         gu = cols.at( u ) > 0 ? u : u + N;
         assert( g.getNeighbor( gu ).count( gv ) );
         Expr<REAL>& ge = g.getExpr( gu, gv );
         auto& gcols = ge.getCols();
         msg.info( "\tresolve on u {} with ", u );
         ge.print();
         assert( gcols.count( u ) && gcols.count( v ) );
         assert( gv > N ? gcols.at( v ) < 0 : gcols.at( v ) > 0 );
         assert( gcols.at( u ) * cols.at( u ) < 0 );
         resolveWithLit( ansExp, ge, u, v );
         msg.info( "resolve on {} ", u );
         ge.print();
         ansExp.print();
      }
      return;
   };

   auto& es = this->exprs.getExprs();
   std::unordered_set<Expr<REAL>, boost::hash<Expr<REAL>>> addExprs;
   Graph<REAL> g;
   g.init( this->exprs.getVarNum() );
   int N = g.getNodeNum();
   if( !buildGraph( es, g ) ) //* no binary edge
   {
      msg.info( "no bianry edges\n" );
      return;
   }
   g.print();
   msg.info( "-----end graph-----\n" );

   this->hbrCallNum++;
   std::unordered_set<int> commonLits;
   for( auto D : es )
   {
      auto& cols = D.getCols();
      if( cols.size() <= 2 ) //* jump short cons
         continue;
      for( auto i : cols )
      {
         commonLits.clear();
         //* u is the variable to save after resolution
         //* the common literals should have same neghbors v
         int u = i.first;
         int v;
         g.findCommonLit( D, commonLits, u );
         if( commonLits.size() )
            std::cout << "\nsaved lits: " << u << ": " << commonLits;

         if( !commonLits.empty() )
         {
            for( auto gv : commonLits ) // v is the common lit in graph
            {
               v = gv > N ? gv - N : gv;
               assert( !cols.count( v ) || ( cols.count( v ) && u == v ) );
               Expr<REAL> e;
               resolve( g, D, e, u, v, gv );
               assert( ( !cols.count( v ) && e.getVarsSize() == 2 &&
                         e.getCols().count( u ) && e.getCols().count( v ) ) ||
                       ( cols.count( v ) && e.getVarsSize() < 2 ) );
               addExprs.emplace( std::move( e ) );
               this->hbrAddedNum++;
            }
         }
         else
         {
            continue;
         }
      }
   }
   int initialN = es.size();
   int addedN = addExprs.size();
   for( auto e : addExprs )
   {
      exprs.addExpr( e );
   }
   assert( exprs.getCosNum() == initialN + addedN );

   msg.info( "Added Num {}\n", this->hbrAddedNum );
   return;
}

template <typename REAL>
void
SATPreSolver<REAL>::presolve()
{
   this->pbStatus = 1;
   hyperBinaryResolution();
   if( redDelNum || hbrAddedNum )
      this->presolveStatus = 1;
   if( onlyPreSolve )
      return;

   strpair rsSol;
   if( this->presolveStatus == 2 )
   {
      return;
   }
   else if( this->presolveStatus == 1 )
   {
      std::string s = "* #variable= " + aux::tos( exprs.getVarNum() ) +
                      " #constraint= " + aux::tos( exprs.getCosNum() ) + "\n";

      auto& es = exprs.getExprs();
      auto& obje = exprs.getObj();
      if( this->instanceType == fileType::opt )
         s += "min: " + aux::ObjExpr2String( obje.getCols() ) + "\n";
      int cnt = 0;
      for( auto& e : es )
      {
         cnt++;
         s += aux::Expr2String( e.getCols(), e.getDeg() ) + "\n";
      }
      msg.info( "write constraint number {}", cnt );
      rsSol = runRoundingSat::runforSAT( s, this->inputIns ); // status, obj
   }
   else if( this->presolveStatus == 0 )
   {
      rsSol = runRoundingSat::runforSAT( this->inputIns );
   }

   std::cout << rsSol << std::endl;
   this->solutionStatus = rsSol.first == "UNSATISFIABLE"
                              ? solStat::UNSATISFIABLE
                              : solStat::SATISFIABLE;
   if( this->instanceType == fileType::opt &&
       this->solutionStatus == solStat::SATISFIABLE )
   {
      assert( rsSol.second != "" );
      bigint t( rsSol.second );
      this->origobj = t;
   }

   return;
}

template <typename REAL>
void
SATPreSolver<REAL>::printSolution()
{
   std::cout << std::setw( 16 ) << "BOOLEAN " << pbStatus
             << std::endl; // 0 fail 1 pass
   // 0: opt, 1: dec
   std::cout << std::setw( 16 ) << "FILE "
             << std::log2( utils::as_integer( this->instanceType ) )
             << std::endl;
   // -1: already solved, 0: unchanged, 1: reduced,
   //  2: unbounded or infeasible, 3: unbounded, 4: infeasible
   std::cout << std::setw( 16 ) << "PRESOLVE_STAT " << this->presolveStatus
             << std::endl;
   if( !this->onlyPreSolve )
   {
      // 0: UNSAT, 1:SAT
      std::cout << std::setw( 16 ) << "SAT "
                << std::log2( utils::as_integer( this->solutionStatus ) )
                << std::endl;
      if( this->solutionStatus != solStat::UNSATISFIABLE &&
          this->instanceType == fileType::opt )
      {
         std::cout << std::setw( 16 ) << "OBJ " << this->origobj << std::endl;
      }
      else if( this->instanceType == fileType::dec )
      {
         ;
      }
   }
}

template <typename REAL>
void
SATPreSolver<REAL>::writePresolvers( const std::string& inFileName )
{
   std::string inpath = "../param/printPresolveNames.txt";
   std::string outpath =
       inFileName.substr( 0, inFileName.find_last_of( "//" ) + 1 ) +
       "0-paraDoc.txt";
   std::ifstream infile( inpath );
   std::ofstream outfile( outpath, std::ios::app );
   outfile.setf( std::ios::left, std::ios::adjustfield );

   assert( !infile.fail() );
   assert( !outfile.fail() );
   outfile << inFileName.substr( inFileName.find_last_of( "//" ) + 1 ) + '\n';
   outfile << '\t' << this->redCallNum << " " << this->redDelNum << std::endl;
   outfile << '\t' << this->hbrCallNum << " " << this->hbrAddedNum << std::endl;
   outfile << std::endl;

   outfile.close();
   infile.close();
   return;
}
template class SATPreSolver<bigint>;
} // namespace pre