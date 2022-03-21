#pragma once

#include "utils.hpp"

namespace pre {

template <typename REAL>
class MIPPreSolver {
   public:
    // export
    papilo::Problem<REAL> getOriginalProblem();
    void printAbstractProblem();
    void printDetailedProblem();

    // main functionality
    void buildProblem(std::string inFileName);
    int runPresolve();
    void alreadySolve();
    bool PBCheck();
    std::string collectResult();
    void postSolve(std::string& rsSol);

    // helper function
    std::string writeConstraint(const papilo::SparseVectorView<REAL>& row,
                                const papilo::Vec<std::string>& varnames,
                                const int& flip, const std::string& op, const REAL& deg);

   private:
    // PaPILO
    papilo::ProblemBuilder<REAL> builder;
    papilo::Problem<REAL> problem;
    papilo::Presolve<REAL> presolve;
    papilo::PresolveResult<REAL> result;
    papilo::Num<REAL> num{};

    const double eps = 1e-6;
};

}  // namespace pre
