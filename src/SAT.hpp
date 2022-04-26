#pragma once

#include "Constr.hpp"
#include "parsing.hpp"

namespace pre {
template <typename REAL>
class SATPreSolver {
   public:
    void buildProblem(const std::string& inFileName);
    void redundancyDetection();

   private:
    ExprPool<REAL> exprs;
    // overall container
    int presolveStatus;
    fileType instanceType;
    solStat solutionStatus;
    bool pbStatus;
    bool onlyPreSolve;
    std::string inputIns;

    // presolving information
    int redDelNum = 0;
    int redCallNum = 0;
    double redElapsedTime;
    std::vector<std::pair<Expr<REAL>, Expr<REAL>>> redRelation;
};
}  // namespace pre