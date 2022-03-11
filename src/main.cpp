#include <cstring>
#include <iostream>

#include "MIP.hpp"
#include "runRoundingSat.hpp"

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

    // run PaPILO
    pre::MIPPreSolver<double>
        mSolver;
    mSolver.buildProblem(infile);
    papilo::Problem<double> problem = mSolver.getOriginalProblem();
    // mSolver.printAbstractProblem();
    std::cout << "---------------Start Running PaPILO--------------" << std::endl;
    int status = mSolver.runPresolve();
    std::cout << "---------------END Running PaPILO--------------" << std::endl;

    std::cout << "S " << status << std::endl;
    if (status == -1) {
        mSolver.alreadySolve();
    } else if (status == 0 || status == 1) {
        if (mSolver.PBCheck()) std::cout << "P 1 pass Pseudo-Boolean check" << std::endl;
        if (onlyPreSolve == 0) {
            std::string preInfo = mSolver.collectResult();
            std::cout << "C running roundingSat .. " << std::endl;
            std::string rsSol = pre::runRoundingSat::run(preInfo, infile);
            std::cout << "C start postsolve .. " << std::endl;
            mSolver.postSolve(rsSol);
        }
    } else {
        std::cout << "C PaPILO detec to be infeasible or unbounded .. " << std::endl;
    }

    return 0;
}