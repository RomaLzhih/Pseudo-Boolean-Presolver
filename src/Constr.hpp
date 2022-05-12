#pragma once

#include <boost/algorithm/string.hpp>

#include "auxiliary.hpp"
#include "typedef.hpp"

namespace pre
{
template <typename REAL>
struct Expr
{
 public:
   bool
   operator==( const Expr& b ) const
   {
      return hashValue == b.hashValue;
   }
   Expr() {}
   Expr( const std::string& lhs, const std::string& rhs );

   void
   invert();

   void
   negate();

   void
   delateCol( int u )
   {
      cols.erase( u );
   };

   void
   setCoeff( int u, REAL val )
   {
      cols[u] = val;
   }

   void
   setDeg( REAL val )
   {
      deg = val;
   }

   void
   setHash( std::size_t h )
   {
      this->hashValue = h;
   }

   void
   print() const;

   const int
   getVarsSize() const
   {
      return cols.size();
   }

   inline const REAL&
   getDeg() const
   {
      return deg;
   }
   inline const std::unordered_map<int, REAL>&
   getCols() const
   {
      return cols;
   }
   inline void
   getLits( std::vector<int>& vec ) const
   {
      vec.clear();
      auto key_selector = []( auto p ) { return p.first; };
      vec.resize( cols.size() );
      std::transform( cols.begin(), cols.end(), vec.begin(), key_selector );
   }
   const std::size_t
   getHash() const
   {
      return hashValue;
   }

   // hash function return
   friend std::size_t
   hash_value( Expr<REAL> const& b )
   {
      std::size_t seed = b.hashValue;
      return seed;
   }

 private:
   std::unordered_map<int, REAL> cols;
   REAL deg;
   std::size_t hashValue;
};

template <typename REAL>
struct ExprPool
{
 public:
   ExprPool() {}
   inline void
   addExpr( Expr<REAL>& e )
   {
      // e.setHash( ++ghostCode );
      exprs.emplace( e );
   }
   void
   addObj( Expr<REAL>& _obj )
   {
      // _obj.setHash( ++ghostCode );
      this->obj = _obj;
   }
   void
   delateExpr( const Expr<REAL>& e )
   {
      exprs.erase( e );
   }
   void
   setSize( const int& n, const int& m )
   {
      N = n, M = m;
   }
   auto&
   getExprs()
   {
      return exprs;
   }
   auto&
   getObj()
   {
      return obj;
   }
   std::size_t&
   getGhostCode()
   {
      return this->ghostCode;
   }
   const int&
   getVarNum()
   {
      return N;
   }
   const int&
   getOrigConsNum()
   {
      return M;
   }
   int
   getCosNum()
   {
      return exprs.size();
   }
   void
   print()
   {
      obj.print();
      for( auto e : exprs )
         e.print();
   }
   void
   toString( const fileType& instanceType );
   const std::string&
   getStringView()
   {
      return this->stringView;
   }

 private:
   std::unordered_set<Expr<REAL>, boost::hash<Expr<REAL>>> exprs;
   Expr<REAL> obj;
   int N;
   int M;
   std::size_t ghostCode;
   std::string stringView;
};

template <typename REAL>
struct Graph
{
 public:
   void
   init( const int& n )
   {
      g.resize( 2 * n + 1 );
      N = n;
   };

   void
   addEdge( const int& u, const int& v, const Expr<REAL>& expr );

   const std::unordered_set<int>&
   getNeighbor( const int& u ) const
   {
      return g[u];
   };

   void
   findCommonLit( const Expr<REAL>& expr, std::unordered_set<int>& ans,
                  const int& ell );

   Expr<REAL>&
   getExpr( const int& u, const int& v );

   int
   getNodeNum() const
   {
      return N;
   }

   void
   print();

 private:
   papilo::Message msg{};

   std::vector<std::unordered_set<int>> g;
   std::map<std::pair<int, int>, Expr<REAL>> edges;
   int N;
};
} // namespace pre