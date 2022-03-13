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
    void setPara();
    int runPresolve();
    void alreadySolve();
    bool PBCheck();
    std::string collectResult();
    void postSolve(std::string& rsSol);

    // helper function
    REAL getCoeff(const std::string& s);
    std::string tos(const REAL& num);
    std::string writeConstraint(const papilo::SparseVectorView<REAL>& row,
                                const papilo::Vec<std::string>& varnames,
                                int flip, std::string op, REAL deg);

   private:
    // PaPILO
    papilo::ProblemBuilder<REAL> builder;
    papilo::Problem<REAL> problem;
    papilo::Presolve<REAL> presolve;
    papilo::PresolveResult<REAL> result;

    const double eps = 1e-6;
};

}  // namespace pre
