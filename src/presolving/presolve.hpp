#pragma once

#include "Solver.hpp"
#include "presolving/MIP.hpp"
#include "presolving/SAT.hpp"

namespace pre {
class PreSolver {
 public:
  void setInputPath(const std::string& infilename) { this->inFileName = infilename; }
  std::string getPreSolvedPath() { return simPath; }

 private:
  std::string inFileName;
  std::string simPath;
};

}  // namespace pre