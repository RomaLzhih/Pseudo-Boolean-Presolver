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
   SATPreSolver() {}
   SATPreSolver( const std::string& input, const std::string& param )
   {
      this->inputIns = input;
      this->paramFile = param;
   }
   void
   buildProblem();
   void
   redundancyDetection( papilo::Timer*& timer );
   void
   redundancyDetectionHeuristic( papilo::Timer*& timer );
   void
   hyperBinaryResolution( papilo::Timer*& timer );
   void
   presolve();
   void
   printSolution();
   void
   writePresolvers( const std::string& inFileName );
   const int&
   getPresolveStatus()
   {
      return this->presolveStatus;
   }
   void
   setOnlyPresolve( int& v )
   {
      this->onlyPreSolve = v;
   }
   void
   setLoggerPath( const std::string& lp )
   {
      this->loggerPath = lp;
   }

 private:
   ExprPool<REAL> exprs;
   papilo::Message msg{};

   // redundacy parameter
   int enablered = 0;
   int redCmpSize = 800;
   bool parallelRed = 0;

   // hyper binary resolution parameter
   int enablehbr = 0;
   bool parallelHbr = 0;

   // overall container
   int presolveStatus = 0; //* 0 unchanged 1 reduced 2 UNSAT
   fileType instanceType;
   solStat solutionStatus;
   bool pbStatus;
   bool onlyPreSolve;
   std::string inputIns = "";
   std::string paramFile = "";
   std::string loggerPath;
   bigint origobj;

   // presolving information
   int redDelNum = 0;
   int redCallNum = 0;
   int singleSubsumption = 0;
   int noneSingleSubsumption = 0;
   int hbrAddedNum = 0;
   int hbrFindNum = 0;
   int hbrCallNum = 0;
   double redElapsedTime = 0.0;
   double hbrElapsedTime = 0.0;
   double timelimit = 0.0;
   double totalTime = 0.0;
   double RSTime = 0.0;
   std::vector<std::pair<Expr<REAL>, Expr<REAL>>> redRelation;
};
} // namespace pre