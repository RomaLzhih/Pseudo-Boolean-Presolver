#include "presolving/runRoundingSat.hpp"

namespace pre {

std::string runRoundingSat::getMIPSolvedFile(const std::string& preInfo, std::string infile) {
  while (*infile.rbegin() != '.') infile.pop_back();
  std::string newInsPath = infile + "pre.opb";
  std::ofstream out(newInsPath);
  out << preInfo;
  out.close();

  std::string line;
  std::string sol = "";
  std::string status = "";

  return newInsPath;
}  // namespace runRoundingSat

}  // namespace pre