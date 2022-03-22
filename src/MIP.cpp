
#include "MIP.hpp"

#include <boost/algorithm/string.hpp>

namespace pre {
// export
template <typename REAL>
papilo::Problem<REAL> MIPPreSolver<REAL>::getOriginalProblem() {
    return problem;
}

template <typename REAL>
void MIPPreSolver<REAL>::printAbstractProblem() {
    utils::printAbstractProblem(problem);
}

template <typename REAL>
void MIPPreSolver<REAL>::printDetailedProblem() {
    utils::printDetailedProblem(problem);
}

template <typename REAL>
void MIPPreSolver<REAL>::setOnlyPresolve(bool flag) {
    onlyPreSolve = flag;
    return;
}

// main functionality
template <typename REAL>
void MIPPreSolver<REAL>::buildProblem(std::string inFileName) {
    std::ifstream infile(inFileName);
    assert(!infile.fail());
    inputIns = inFileName;

    instanceType = parser::opb_read(infile, builder) ? fileType::opt : fileType::dec;

    infile.close();
    problem = builder.build();
}

template <typename REAL>
int MIPPreSolver<REAL>::runPresolve() {
    auto setPara = [&]() {
        std::string paraPath = "../parameters.test.txt";
        std::ifstream parafile(paraPath);
        assert(!parafile.fail());

        std::string line;
        papilo::ParameterSet paramset = presolve.getParameters();
        while (std::getline(parafile, line)) {
            if (line.empty() || line[0] == '#') continue;
            int pos = line.find_first_of("=");
            std::string para = line.substr(0, pos - 1);
            std::string val = line.substr(pos + 2);
            // std::cout << para << " " << val << std::endl;
            paramset.parseParameter(para.c_str(), val.c_str());
        }
        parafile.close();
    };

    presolve.addDefaultPresolvers();
    setPara();
    result = presolve.apply(problem);

    num.setEpsilon(presolve.getEpsilon());  // use same tollerance with papilo
    num.setFeasTol(presolve.getFeasTol());
    num.setHugeVal(presolve.getHugeVal());

    if (problem.getNCols() == 0)
        return -1;  // already solve
    else
        return (int)utils::as_integer(result.status);  // papilo status
}

template <typename REAL>
void MIPPreSolver<REAL>::alreadySolve() {
    // papilo already solved an opt or find an satisfying assignment
    papilo::Solution<REAL> solution{};
    papilo::Solution<REAL> empty_sol{};
    empty_sol.type = papilo::SolutionType::kPrimal;
    if (result.postsolve.postsolveType == PostsolveType::kFull)
        empty_sol.type = papilo::SolutionType::kPrimalDual;

    papilo::Message msg{};
    papilo::Postsolve<REAL> postsolve{msg, num};
    postsolve.undo(empty_sol, solution, result.postsolve);
    sol = solution.primal;
    if (instanceType == fileType::opt) {
        origobj = result.postsolve.getOriginalProblem().computeSolObjective(solution.primal);
    }
    solutionStatus = solStat::SATISFIABLE;
    pbStatus = true;
}

template <typename REAL>
bool MIPPreSolver<REAL>::PBCheck() {
    papilo::VariableDomains<REAL>& vars = problem.getVariableDomains();
    // std::cout << problem.getNCols() << std::endl;
    for (int i = 0; i < problem.getNCols(); i++) {
        if (!vars.isBinary(i)) {
            return false;
            throw std::invalid_argument("NON-BOOLEAN VARIABLE AFTER PRESOVE");
        }
    }
    return true;
}

template <typename REAL>
std::string MIPPreSolver<REAL>::collectResult() {
    std::string str = "";

    const papilo::ConstraintMatrix<REAL>& consmatrix = problem.getConstraintMatrix();
    const papilo::Vec<std::string>& varnames = problem.getVariableNames();
    const papilo::Objective<REAL>& objective = problem.getObjective();
    const papilo::Vec<papilo::ColFlags>& col_flags = problem.getColFlags();
    const papilo::Vec<papilo::RowFlags>& row_flags = problem.getRowFlags();
    const papilo::Vec<REAL>& lhs = consmatrix.getLeftHandSides();
    const papilo::Vec<REAL>& rhs = consmatrix.getRightHandSides();

    int nCols = consmatrix.getNCols();
    int nRows = consmatrix.getNRows();

    str += "* #variable= " + aux::tos(nCols) + " #constraint= " + aux::tos(nRows) + "\n";

    // print objective
    str += "min: ";
    const papilo::Vec<REAL> objCoeff = objective.coefficients;
    for (int i = 0; i < objCoeff.size(); i++) {
        if (num.isZero(objCoeff[i])) continue;
        assert(num.isIntegral(objCoeff[i]));
        str += aux::tos(num.round(objCoeff[i])) + " " + varnames[i] + " ";
    }
    str += ";\n";

    // print constraint
    for (int i = 0; i < nRows; i++) {
        const papilo::SparseVectorView<REAL>& row = consmatrix.getRowCoefficients(i);

        const bool L = row_flags[i].test(papilo::RowFlag::kLhsInf) ? 1 : 0;
        const bool R = row_flags[i].test(papilo::RowFlag::kRhsInf) ? 1 : 0;

        if (!L && R) {  // a <= x
            str += writeConstraint(row, varnames, 1, ">=", lhs[i]);
        } else if (L && !R) {  // x <= b
            str += writeConstraint(row, varnames, -1, ">=", (REAL)(-1 * rhs[i]));
        } else if (!L && !R) {
            if (lhs[i] == rhs[i]) {  // a = x = b
                assert(row_flags[i].test(papilo::RowFlag::kEquation));
                str += writeConstraint(row, varnames, 1, "=", lhs[i]);
            } else {  // a <= x <= b, a != b
                assert(!row_flags[i].test(papilo::RowFlag::kEquation));
                str += writeConstraint(row, varnames, 1, ">=", lhs[i]);
                str += writeConstraint(row, varnames, -1, ">=", (REAL)(-1 * rhs[i]));
            }
        } else {
            throw std::invalid_argument("Row " + std::to_string(i) + " contains invalid constraint. LhsInf: " + std::to_string(row_flags[i].test(papilo::RowFlag::kLhsInf)) + " RhsInf: " + std::to_string(row_flags[i].test(papilo::RowFlag::kRhsInf)));
        }
    }

    return str;
}

template <typename REAL>
void MIPPreSolver<REAL>::postSolve(strpair& rsSol) {
    if (rsSol.first == "UNSATISFIABLE") {
        solutionStatus = solStat::UNSATISFIABLE;
        return;
    }
    assert(rsSol.first == "OPTIMUM FOUND" || rsSol.first == "SATISFIABLE");
    assert(rsSol.second.size());
    papilo::Vec<REAL> reducedsolvals;
    std::vector<std::string> splitSols;
    boost::split(splitSols, rsSol.second, boost::is_any_of(" "), boost::token_compress_on);
    for (auto s : splitSols) {
        if (s[0] == '+' || s[0] == 'x')
            reducedsolvals.push_back(1);
        else if (s[0] == '-')
            reducedsolvals.push_back(0);
        else
            throw std::invalid_argument("INVALID ROUNDINGSAT SOLUTION: NON +/-/x");
    }
    if (reducedsolvals.size() != problem.getConstraintMatrix().getNCols()) {
        throw std::invalid_argument("UNMACHED SOLUTION, REQUIRE: " + std::to_string(problem.getConstraintMatrix().getNCols()) + " OBTAIN: " + std::to_string(reducedsolvals.size()));
    }

    papilo::Message msg{};
    papilo::Postsolve<REAL> postsolve{msg, num};
    papilo::Solution<REAL> reducedsol(std::move(reducedsolvals));
    papilo::Solution<REAL> origsol;
    PostsolveStatus status = postsolve.undo(reducedsol, origsol, result.postsolve);

    origobj = result.postsolve.getOriginalProblem().computeSolObjective(origsol.primal);
    assert(num.isIntegral(origobj));
    origobj = num.round(origobj);

    if (status == PostsolveStatus::kOk) {
        std::string sign;
        sol = origsol.primal;
        solutionStatus = solStat::SATISFIABLE;
    } else {
        throw std::invalid_argument("PaPILO POSTSOLVE FAILED");
    }

    return;
}

// helper function
template <typename REAL>
std::string MIPPreSolver<REAL>::writeConstraint(const papilo::SparseVectorView<REAL>& row,
                                                const papilo::Vec<std::string>& varnames,
                                                const int& flip, const std::string& op, const REAL& deg) {
    auto IntegralCoeff = [&](const papilo::Vec<REAL>& vals, papilo::Vec<bigint>& ans) {
        // a/b
        papilo::Vec<bigint> a(vals.size());
        papilo::Vec<bigint> b(vals.size());

        bool allInteger = true;
        for (int i = 0; i < vals.size(); i++) {
            if (num.isIntegral(vals[i])) {
                a[i] = (bigint)num.round(aux::abs(vals[i]));
                b[i] = 1;
            } else {
                allInteger = false;
                a[i] = aux::numerator(aux::abs(vals[i]));
                b[i] = aux::denominator(aux::abs(vals[i]));
            }
        }

        if (allInteger) {
            for (int i = 0; i < ans.size(); i++) {
                ans[i] = a[i];
                if (num.isLT(vals[i], 0)) {
                    ans[i] *= -1;
                }
            }
            return;
        } else {
            std::cout << "C derational" << std::endl;
            bigint _gcd = aux::min(a);
            bigint _lcm = aux::max(b);
            for (int i = 0; i < b.size(); i++) {
                _lcm = aux::lcm(_lcm, b[i]);
            }
            for (int i = 0; i < a.size(); i++) {
                ans[i] = _lcm / b[i] * a[i];
                _gcd = aux::gcd(_gcd, ans[i]);
            }
            std::cout << _lcm << " " << _gcd << std::endl;
            for (int i = 0; i < ans.size(); i++) {
                assert(num.isIntegral((REAL)(ans[i]) / (REAL)(_gcd)));
                ans[i] /= _gcd;
                if (num.isLT(vals[i], 0)) {
                    ans[i] *= -1;
                }
                assert(num.isLT((REAL)ans[i], 0) == num.isLT(vals[i], 0));
            }
        }
    };

    const REAL* rowVals = row.getValues();
    const int* indices = row.getIndices();
    const auto len = row.getLength();

    papilo::Vec<REAL> coeffVal(rowVals, rowVals + len);
    coeffVal.emplace_back(deg);
    papilo::Vec<bigint> simVal(coeffVal.size());
    IntegralCoeff(coeffVal, simVal);

    // papilo::Vec<REAL> coeffVal{1.5, 0.75, 1.125, 10.5};
    // papilo::Vec<bigint> simVal(coeffVal.size());
    // papilo::Vec<bigint> ans{4, 2, 3, 16};
    // IntegralCoeff(coeffVal, simVal, num);
    // std::cout << simVal << std::endl;
    // assert(coeffVal[0] == 1);

    std::string s = "";
    for (int j = 0; j < len; j++) {
        s += aux::tos((REAL)(flip * simVal[j])) + " " + varnames[indices[j]] + " ";
    }
    s += op + " " + aux::tos(simVal[len]) + " ;\n";
    return s;
}

template <typename REAL>
void MIPPreSolver<REAL>::run() {
    std::cout << "---------------Start Running PaPILO--------------" << std::endl;
    presolveStatus = runPresolve();
    std::cout << "---------------END Running PaPILO--------------" << std::endl;

    if (presolveStatus == -1) {  // already solved
        alreadySolve();
        std::cout << "B " << pbStatus << std::endl;// 0 fail 1 pass
    } else if (presolveStatus == 0 || presolveStatus == 1) {
        pbStatus = PBCheck();
        std::cout << "B " << pbStatus << std::endl;
        if (!onlyPreSolve) {
            std::string preInfo = collectResult();
            std::cout << "C running roundingSat .. " << std::endl;
            strpair rsSol = runRoundingSat::run(preInfo, inputIns);
            std::cout << "C start postsolve .. " << std::endl;
            postSolve(rsSol);
        }
    } else {
        solutionStatus = solStat::UNSATISFIABLE;
        std::cout << "C PaPILO detec to be infeasible or unbounded .. " << std::endl;
    }
}

template <typename REAL>
void MIPPreSolver<REAL>::printSolution() {
    // 0: opt, 1: dec
    std::cout << "F " << std::log2(utils::as_integer(instanceType)) << std::endl;
    // -1: already solved, 0: unchanged, 1: reduced,
    //  2: unbounded or infeasible, 3: unbounded, 4: infeasible
    std::cout << "P " << presolveStatus << std::endl;
    if (!onlyPreSolve) {
        // 0: UNSAT, 1:SAT
        std::cout << "S " << std::log2(utils::as_integer(solutionStatus)) << std::endl;
        if (solutionStatus != solStat::UNSATISFIABLE && instanceType == fileType::opt) {
            std::cout << "O " << origobj << std::endl;
        } else if (instanceType == fileType::dec) {
            ;
        }
    }
}

template class MIPPreSolver<papilo::Rational>;

}  // namespace pre