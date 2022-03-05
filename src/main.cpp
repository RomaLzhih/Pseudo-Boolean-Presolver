#include "MIP.hpp"
#include "runRoundingSat.hpp"

#include <cstring>
#include <iostream>

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
    infile = "../" + infile;  // add prefix

    // run PaPILO
    pre::MIPPreSolver<double> mSolver;
    mSolver.buildProblem(infile);
    papilo::Problem<double> problem = mSolver.getOriginalProblem();
    // mSolver.printAbstractProblem();
    int status = mSolver.runPresolve();

    std::cout << "MIP Presolve status: " << status << std::endl;
    std::string preInfo = mSolver.collectResult();

    // run roundingSat
    std::cout << "Running roundingSat .. " << std::endl;
    std::string rsSol = pre::runRoundingSat::run(preInfo, infile);

    // postsolve
    std::cout << "Start postsolve .. " << std::endl;
    mSolver.postSolve(rsSol);

    return 0;
}