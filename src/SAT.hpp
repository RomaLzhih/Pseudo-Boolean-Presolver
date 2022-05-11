#pragma once

#include "Constr.hpp"
#include "parsing.hpp"
#include "runRoundingSat.hpp"

namespace pre
{
template <typename REAL>
class SATPreSolver
{
 public:
   void
   buildProblem( const std::string& inFileName );
   void
   redundancyDetection();
   void
   hyperBinaryResolution();
   void
   presolve();
   void
   printSolution();
   void
   writePresolvers( const std::string& inFileName );
   void 
   setOnlyPresolve(int& v){
      this->onlyPreSolve = v;
   }

 private:
   ExprPool<REAL> exprs;
   papilo::Message msg{};

   // redundacy parameter
   int enablered = 0;
   int enablehbr = 1;
   int redCmpSize = 800;

   // hyper binary resolution parameter

   // overall container
   int presolveStatus = 0;
   fileType instanceType;
   solStat solutionStatus;
   bool pbStatus;
   bool onlyPreSolve;
   std::string inputIns;
   bigint origobj;

   // presolving information
   int redDelNum = 0;
   int redCallNum = 0;
   int hbrAddedNum = 0;
   int hbrCallNum = 0;
   double redElapsedTime=0.0;
   double hbrElapsedTime=0.0;
   double totTime = 0.0;
   double rsTime = 0.0;
   std::vector<std::pair<Expr<REAL>, Expr<REAL>>> redRelation;
};
} // namespace pre