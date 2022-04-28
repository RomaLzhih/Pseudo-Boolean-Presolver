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

int main(int argc, char *argv[]) {
    std::string infile = argv[1];
    int onlyPreSolve = std::stoi(argv[2]);
    int solvertype = std::stoi(argv[3]);
    // std::string infile = "../test/opt/p0033.opb";
    // int onlyPreSolve = std::stoi("0");
    // int solvertype = std::stoi("1");

    if (solvertype == 0) {  // run SAT
        pre::SATPreSolver<pre::bigint> sSolver;
        sSolver.buildProblem(infile);
        // sSolver.redundancyDetection();
        // sSolver.writePresolvers(infile);

    } else if (solvertype == 1) {  // run papilo
        pre::MIPPreSolver<papilo::Rational> mSolver;
        mSolver.setOnlyPresolve(onlyPreSolve);
        mSolver.buildProblem(infile);
        papilo::Problem<papilo::Rational> problem =
            mSolver.getOriginalProblem();
        // mSolver.printDetailedProblem();

        mSolver.run();
        mSolver.printSolution();
        mSolver.writePresolvers(infile);
    } else {
    }
    return 0;
}