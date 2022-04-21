#include "presolving/presolve.hpp"

namespace pre {

void PreSolver::MIPSolve() {
  bool onlyPreSolve = false;  // TODO: pass as parameter

  MIPSolver.setOnlyPresolve(onlyPreSolve);
  MIPSolver.buildProblem(inFileName);

  std::cout << "---------------Start Running PaPILO--------------" << std::endl;
  int presolveStatus = MIPSolver.runPresolve();
  MIPSolver.setPreSolveStatus(presolveStatus);
  std::cout << "---------------END Running PaPILO--------------" << std::endl;

  if (presolveStatus == -1) {  // already solved
    MIPSolver.alreadySolve();
    std::cout << "B " << MIPSolver.getPBStatus() << std::endl;  // 0 fail 1 pass
  } else if (presolveStatus == 0 || presolveStatus == 1) {
    MIPSolver.setPBStatus(MIPSolver.PBCheck());
    std::cout << "B " << MIPSolver.getPBStatus() << std::endl;
    if (!onlyPreSolve) {
      std::string preInfo = MIPSolver.collectResult();
      this->simPath = runRoundingSat::getMIPSolvedFile(preInfo, inFileName);
    }
  } else {
    MIPSolver.setSolutionStat(solStat::UNSATISFIABLE);
    std::cout << "C PaPILO detec to be infeasible or unbounded .. " << std::endl;
  }

  return;
}

void PreSolver::MIPPostSolve(const rs::Solver& rsSolver) {
  const std::vector<rs::Lit>& sol = rsSolver.lastSol;
  pre::solStat rsStat = (!rsSolver.foundSolution()) ? pre::solStat::UNSATISFIABLE : pre::solStat::SATISFIABLE;
  std::vector<int> rsSol(rsSolver.getNbOrigVars());
  for (rs::Var v = 1; v <= (rs::Var)rsSolver.getNbOrigVars(); ++v) {
    rsSol[v - 1] = sol[v] > 0 ? 1 : 0;
  }
  MIPSolver.postSolve(rsSol, rsStat);
  return;
}

void PreSolver::printSolution(){
  MIPSolver.printSolution();
  MIPSolver.writePresolvers(this->inFileName);
  return;
}

}  // namespace pre
