#pragma once

#include "parsing.hpp"
#include "runRoundingSat.hpp"

namespace pre
{

template <typename REAL>
class MIPPreSolver
{
 public:
   // export
   papilo::Problem<REAL>
   getOriginalProblem();
   void
   printAbstractProblem();
   void
   printDetailedProblem();
   void
   setOnlyPresolve( bool flag );
   void
   setLoggerPath( const std::string& lp )
   {
      this->loggerPath = lp;
   }
   double&
   getTotalTime()
   {
      return totalTime;
   }
   double&
   getRSTime()
   {
      return RSTime;
   }

   // main functionality
   void
   run();
   void
   buildProblem( const std::string& inFileName );
   void
   printSolution();
   void
   writePresolvers( const std::string& inFileName );

 private:
   // helper function
   int
   runPresolve();
   void
   alreadySolve();
   bool
   PBCheck();
   std::string
   collectResult();
   void
   postSolve( strpair& rsSol );

   // helper function
   std::string
   writeConstraint( const papilo::SparseVectorView<REAL>& row,
                    const papilo::Vec<std::string>& varnames, const int& flip,
                    const std::string& op, const REAL& deg );

 private:
   // PaPILO
   papilo::ProblemBuilder<REAL> builder;
   papilo::Problem<REAL> problem;
   papilo::Presolve<REAL> presolve;
   papilo::PresolveResult<REAL> result;
   papilo::Num<REAL> num{};

   // overall container
   int presolveStatus;
   fileType instanceType;
   solStat solutionStatus;
   bool pbStatus;
   papilo::Vec<REAL> sol;
   REAL origobj;

   double totalTime = 0.0;
   double RSTime = 0.0;
   double solvingTime = 0.0;

   bool onlyPreSolve;
   std::string inputIns;
   std::string loggerPath;
   const double eps = 1e-6;
};

} // namespace pre
