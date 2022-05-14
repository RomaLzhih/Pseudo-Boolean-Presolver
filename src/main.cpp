#include <cstring>
#include <iostream>

#include "MIP.hpp"
#include "SAT.hpp"
/*
FLOW CHART
    1: feed .opb file to problem builder
    2: run papilo
    3: parser result to .simple.opb
    4: feed .simple.opb to roundingSat
    5: run roundingSat
    6: parser roundingSat result to .postsolve
    7: recover the initial solution
*/

int
main( int argc, char* argv[] )
{
   std::string infile = argv[1];
   std::string SATparam = argv[2];
   std::string MIPparam = argv[3];
   int onlyPreSolve = std::stoi( argv[4] );
   int solvertype = std::stoi( argv[5] );

   if( solvertype == 0 )
   { // run SAT
      pre::SATPreSolver<pre::bigint> sSolver( infile, SATparam );
      sSolver.setOnlyPresolve( onlyPreSolve );
      sSolver.presolve();
      sSolver.printSolution();
      sSolver.writePresolvers( infile );
   }
   else if( solvertype == 1 )
   { // run papilo
      pre::MIPPreSolver<papilo::Rational> mSolver( infile, MIPparam );
      mSolver.setOnlyPresolve( onlyPreSolve );
      mSolver.run();
      mSolver.printSolution();
      mSolver.writePresolvers( infile );
   }
   else if( solvertype == 2 )
   { //* run both

      //* first SAT
      int setOnlyPre = 1;
      std::string midfile =
          infile.substr( 0, infile.find_last_of( '.' ) ) + ".pre.opb";

      pre::SATPreSolver<pre::bigint> sSolver( infile, SATparam );
      pre::MIPPreSolver<papilo::Rational> mSolver( "", MIPparam );
      sSolver.setOnlyPresolve( setOnlyPre );
      sSolver.presolve();

      //* now MIP turn
      mSolver.setOnlyPresolve( onlyPreSolve );
      if( sSolver.getPresolveStatus() == 1 )
         mSolver.setInputIns( midfile );
      else
         mSolver.setInputIns( infile );
      mSolver.run();
      mSolver.printSolution();
      sSolver.writePresolvers( infile );
      mSolver.writePresolvers( infile );
   }
   else
   { // only run roundingSat
      pre::runRoundingSat::runRS( infile );
   }

   return 0;
}