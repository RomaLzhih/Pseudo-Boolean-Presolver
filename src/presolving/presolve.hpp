#pragma once

#include "Solver.hpp"
#include "presolving/MIP.hpp"

namespace rs {
class Solver;

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
}  // namespace rs