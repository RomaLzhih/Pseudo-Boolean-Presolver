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
   this->exprs.print();

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

         rsStat = pre::runRoundingSat::runforSAT( preInfo, this->inputIns );

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
      REAL _gcd = aux::abs( newCol1.at( v ) );
      if( _gcd == 1 ) // special handle for 1
         return;
      for( auto c : newCol1 )
      {
         assert( c.second != 0 );
         _gcd = aux::gcd( _gcd, aux::abs( c.second ) );
      }
      if( _gcd != 1 )
      {
         assert( _gcd > 1 );
         for( auto c : newCol1 )
         {
            e1.setCoeff( c.first, c.second / _gcd );
         }
         e1.setDeg( e1.getDeg() / _gcd );
      }

      return;
   };
   auto resolve = [&]( Graph<REAL>& g, Expr<REAL>& longExp, Expr<REAL>& ansExp,
                       int& saveLit, int& v )
   {
      std::vector<int> lits;
      auto& cols = longExp.getCols();
      longExp.getLits( lits );
      ansExp = longExp;

      int N = g.getNodeNum();
      int gu;
      msg.info( "saveLit {} common lit {} Exp ", saveLit, v );
      longExp.print();

      //* u is the literal to be resolved
      //* v is the common neighbor of u
      //* new constraint should only contains saveLit and v
      for( auto u : lits )
      {
         if( u == saveLit )
            continue;
         gu = cols.at( u ) > 0 ? u : u + N;
         assert( g.getNeighbor( gu ).count( v ) );
         Expr<REAL> ge = g.getExpr( gu, v );
         auto& gcols = ge.getCols();
         assert( gcols.count( u ) && gcols.count( v ) );
         assert( gcols.at( u ) * cols.at( u ) < 0 );
         resolveWithLit( ansExp, ge, u, v );
         msg.info( "resolve on {} ", u );
         ge.print();
         ansExp.print();
      }
      return;
   };

   auto& es = this->exprs.getExprs();
   ExprPool<REAL> addExprs;
   Graph<REAL> g;
   g.init( this->exprs.getVarNum() );
   int N = g.getNodeNum();
   if( !buildGraph( es, g ) ) //* no binary edge
   {
      msg.info( "no bianry edges\n" );
      return;
   }
   //    g.print();

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
         g.findCommonLit( D, commonLits, u );
         if( commonLits.size() )
            std::cout << u << ": " << commonLits << std::endl;

         if( !commonLits.empty() )
         {
            for( auto v : commonLits ) // v is the common lit
            {
               assert( !cols.count( v ) );
               Expr<REAL> e;
               resolve( g, D, e, u, v );
               assert( e.getVarsSize() == 2 );
               assert( e.getCols().count( u ) && e.getCols().count( v ) );
               e.setHash( aux::hashExpr( e.getCols(), e.getDeg() ) );
               addExprs.addExpr( e );
            }
         }
         else
         {
            continue;
         }
      }
   }
   for( auto e : addExprs.getExprs() )
   {
      es.insert( e );
   }
   return;
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
   outfile << std::endl;

   outfile.close();
   infile.close();
   return;
}
template class SATPreSolver<bigint>;
} // namespace pre