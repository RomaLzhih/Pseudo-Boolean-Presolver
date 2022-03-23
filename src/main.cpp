#include <cstring>
#include <iostream>

#include "MIP.hpp"

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

    papilo::Rational a = 1.5;
    const papilo::Num<papilo::Rational> num{};
    std::cout << num.isLT(-1, 0) << std::endl;
    // return 0;

    // run PaPILO
    pre::MIPPreSolver<papilo::Rational> mSolver;
    mSolver.setOnlyPresolve(onlyPreSolve);
    mSolver.buildProblem(infile);
    papilo::Problem<papilo::Rational> problem = mSolver.getOriginalProblem();
    // mSolver.printDetailedProblem();

    mSolver.run();
    mSolver.printSolution();
    mSolver.writePresolvers(infile);

    return 0;
}