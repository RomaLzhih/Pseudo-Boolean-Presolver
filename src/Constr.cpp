#include "Constr.hpp"

namespace pre
{
template <typename REAL>
Expr<REAL>::Expr( const std::string& lhs, const std::string& rhs )
{
   auto to_bigint = [&]( const std::string& s )
   { return s[0] == '+' ? bigint( s.substr( 1 ) ) : bigint( s ); };
   // add LHS
   std::vector<std::string> tokens;
   boost::split( tokens, lhs, boost::is_any_of( " " ),
                 boost::token_compress_on );
   assert( tokens.size() >= 2 );
   for( int l = 0, r = 1; l < tokens.size() && r < tokens.size();
        l += 2, r += 2 )
   {
      this->cols[std::stoi( tokens[r].substr( 1 ) )] = to_bigint( tokens[l] );
   }
   // add deg
   tokens.clear();
   boost::split( tokens, rhs, boost::is_any_of( " " ),
                 boost::token_compress_on );
   this->deg = to_bigint( tokens[0] );
   this->hashValue = aux::hashExpr( this->cols, this->deg );
   return;
}

template <typename REAL>
void
Expr<REAL>::invert()
{
   for( auto c : cols )
      cols[c.first] *= -1;
   this->deg *= -1;
   this->hashValue = aux::hashExpr( this->cols, this->deg );
   return;
}

template <typename REAL>
void
Expr<REAL>::negate()
{
   for( auto c : cols )
      cols[c.first] *= -1;
   this->deg = -this->deg + 1;
   this->hashValue = aux::hashExpr( this->cols, this->deg );
   return;
}

template <typename REAL>
void
Expr<REAL>::print() const
{
   std::cout << aux::Expr2String( cols, deg ) << std::endl;
   return;
}

template <typename REAL>
void
Graph<REAL>::addEdge( const int& u, const int& v, const Expr<REAL>& expr )
{
   int nu = ( ( u + N ) > 2 * N ) ? ( u - N ) : ( u + N );
   assert( nu >= 1 && nu <= 2 * N );
   g[nu].insert( v );
   edges[std::make_pair( nu, v )] = expr;
   // expr.print();
   // msg.info( "u: {} add edge {} to {}\n", u, nu, v );
   return;
}

template <typename REAL>
void
Graph<REAL>::findCommonLit( const Expr<REAL>& expr,
                            std::unordered_set<int>& ans, int ell )
{
   auto& cols = expr.getCols();
   assert( cols.size() > 2 );

   std::vector<int> lits; // ell == lits[]
   expr.getLits( lits );

   // pick the start variable except the jump one
   int stlit = ( ell == lits[0] ) ? lits[1] : lits[0];
   stlit = cols.at( stlit ) > 0 ? stlit : stlit + N; // normalize
   std::unordered_set<int> s = g[stlit];

   // fine elements in s are neighbor of others except ell
   int gv;
   for( auto gu : s )
   {
      bool flag = true;
      for( auto v : lits )
      {
         if( v == ell )
            continue;
         gv = cols.at( v ) > 0 ? v : v + N;
         if( !g[gv].count( gu ) )
         {
            flag = false;
            break;
         }
      }
      if( flag == true )
      {
         ans.insert( gu );
      }
   }
   return;
}

template <typename REAL>
Expr<REAL>&
Graph<REAL>::getExpr( int& u, int& v )
{
   std::pair<int, int> p = std::make_pair( u, v );
   return edges[p];
}

template <typename REAL>
void
Graph<REAL>::print()
{
   msg.info( "nodes num: {} {}\n", g.size(), N );
   for( int i = 0; i < g.size(); i++ )
   {
      msg.info( "For {}: ", i );
      for( auto j : g[i] )
      {
         msg.info( "{} ", j );
         getExpr( i, j ).print();
      }
      msg.info( "\n" );
   }
   return;
}

template struct Expr<bigint>;
template struct ExprPool<bigint>;
template struct Graph<bigint>;
} // namespace pre