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

 private:
   ExprPool<REAL> exprs;
   papilo::Message msg{};

   // redundacy parameter
   int redCmpSize = 800;

   // hyper binary resolution parameter

   // overall container
   int presolveStatus;
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
   double redElapsedTime;
   std::vector<std::pair<Expr<REAL>, Expr<REAL>>> redRelation;
};
} // namespace pre