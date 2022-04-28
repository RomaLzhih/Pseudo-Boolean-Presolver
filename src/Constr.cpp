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

template struct Expr<bigint>;
template struct ExprPool<bigint>;
} // namespace pre