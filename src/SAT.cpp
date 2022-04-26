#include "SAT.hpp"

namespace pre {
template <typename REAL>
void SATPreSolver<REAL>::buildProblem(const std::string& inFileName) {
    std::ifstream infile(inFileName);
    assert(!infile.fail());
    this->inputIns = inFileName;

    this->instanceType = parser::opb_read_to_sat(infile, this->exprs);
    // this->exprs.print();

    infile.close();
}

template <typename REAL>
void SATPreSolver<REAL>::redundancyDetection() {
}

template class SATPreSolver<bigint>;
}  // namespace pre