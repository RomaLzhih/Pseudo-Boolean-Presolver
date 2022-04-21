#pragma once

#include "presolving/MIP.hpp"
#include "run.hpp"
#include "Solver.hpp"

namespace pre {
class PreSolver {
 public:
  void setInputPath(const std::string& infilename) { this->inFileName = infilename; }
  std::string getPreSolvedPath() { return simPath; }

  void MIPSolve();
  void MIPPostSolve(const rs::Solver& rsSolver);
  void printSolution();

 private:
  std::string inFileName;
  std::string simPath;
  MIPPreSolver<papilo::Rational> MIPSolver;
};

}  // namespace pre