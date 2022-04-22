#pragma once

#include "presolving/parsing.hpp"
#include "presolving/runRoundingSat.hpp"

namespace rs{
namespace pre {

template <typename REAL>
class MIPPreSolver {
 public:
  // export
  papilo::Problem<REAL> getOriginalProblem();
  void printAbstractProblem();
  void printDetailedProblem();
  void setPreSolveStatus(const int& val) { this->presolveStatus = val; }
  void setOnlyPresolve(const bool& flag) { this->onlyPreSolve = flag; }
  void setPBStatus(const bool& val) { this->pbStatus = val; }
  void setSolutionStat(const solStat& val) { this->solutionStatus = val; }
  bool getPBStatus() { return pbStatus; }

  // main functionality
  void buildProblem(const std::string& inFileName);
  void printSolution();
  void writePresolvers(const std::string& inFileName);
  void postSolve(const std::vector<int>& rsSol, const pre::solStat& rsStat);

  // helper function
  int runPresolve();
  void alreadySolve();
  bool PBCheck();
  std::string collectResult();

  // helper function
  std::string writeConstraint(const papilo::SparseVectorView<REAL>& row, const papilo::Vec<std::string>& varnames,
                              const int& flip, const std::string& op, const REAL& deg);

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

  bool onlyPreSolve;
  std::string inputIns;
  const double eps = 1e-6;
};

}  // namespace pre
} //rs
