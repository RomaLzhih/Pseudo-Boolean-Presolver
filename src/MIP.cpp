
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

// main functionality
template <typename REAL>
void MIPPreSolver<REAL>::buildProblem(std::string inFileName) {
    std::ifstream infile(inFileName);
    assert(!infile.fail());

    std::string line;
    std::getline(infile, line);
    std::string colNumStr = line.substr(line.find_first_of("=") + 2);
    std::string rowNumStr = line.substr(line.find_last_of("=") + 2);
    int colNum = std::stoi(colNumStr.substr(0, colNumStr.find_first_of(" ")));
    int rowNum = std::stoi(rowNumStr);  //! papilo supports only int number of variables

    std::unordered_map<std::string, int> varMap;

    builder.setNumCols(colNum);
    builder.setNumRows(rowNum);
    // no need to set all since papilo add one-by-one as well
    for (int i = 0; i < colNum; i++) {
        std::string varName = "x" + aux::tos(i + 1);
        builder.setColIntegral(i, true);
        builder.setColName(i, varName);
        builder.setColLb(i, 0);
        builder.setColUb(i, 1);
        varMap[varName] = i;
    }

    // jump comments
    std::string s = "";
    while (infile >> s) {
        if (s.empty())
            continue;
        else if (s[0] == '*')
            std::getline(infile, line);
        else
            break;  // catch 'min:'
    }

    long long coeff;
    std::string varName = "";

    // build objective
    while (infile >> s) {
        if (s == ";") {
            break;
        }
        infile >> varName;
        // std::cout << aux::sto(s) << std::endl;
        builder.setObj(varMap[varName], std::stoll(s));
    }

    // add constraint
    int row = 0;
    std::string RHS;
    while (infile >> s) {
        // std::cout << s << std::endl;
        if (s.empty()) {
            continue;
        } else if (s[0] == '*') {  // TODO: add zeroOrMoreSpace
            std::getline(infile, line);
        } else if (s == ">=") {
            infile >> RHS;
            builder.setRowLhsInf(row, false);
            builder.setRowRhsInf(row, true);
            builder.setRowLhs(row, std::stoll(RHS));
        } else if (s == "=") {
            infile >> RHS;
            builder.setRowLhsInf(row, false);
            builder.setRowRhsInf(row, false);
            builder.setRowLhs(row, std::stoll(RHS));
            builder.setRowRhs(row, std::stoll(RHS));
        } else if (s == ";") {
            row++;
            // std::cout << "row: " << row << std::endl;
        } else {
            infile >> varName;
            if (std::stoll(s) != 0) {  // papilo doesn'REAL allow add zero entry
                builder.addEntry(row, varMap[varName], std::stoll(s));
            }
            // std::cout << s << " " << varName << std::endl;
        }
    }

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
    papilo::Solution<REAL> solution{};
    papilo::Solution<REAL> empty_sol{};
    empty_sol.type = papilo::SolutionType::kPrimal;
    if (result.postsolve.postsolveType == PostsolveType::kFull)
        empty_sol.type = papilo::SolutionType::kPrimalDual;

    papilo::Message msg{};
    papilo::Postsolve<REAL> postsolve{msg, num};
    postsolve.undo(empty_sol, solution, result.postsolve);
    REAL origobj = result.postsolve.getOriginalProblem().computeSolObjective(solution.primal);
    std::cout << "O " << origobj << std::endl;
}

template <typename REAL>
bool MIPPreSolver<REAL>::PBCheck() {
    papilo::VariableDomains<REAL>& vars = problem.getVariableDomains();
    // std::cout << problem.getNCols() << std::endl;
    for (int i = 0; i < problem.getNCols(); i++) {
        if (!vars.isBinary(i)) {
            std::cout << "P 0" << std::endl;
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
void MIPPreSolver<REAL>::postSolve(std::string& rsSol) {
    papilo::Vec<REAL> reducedsolvals;
    std::vector<std::string> splitSols;
    boost::split(splitSols, rsSol, boost::is_any_of(" "), boost::token_compress_on);
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

    REAL origobj = result.postsolve.getOriginalProblem().computeSolObjective(origsol.primal);
    assert(num.isIntegral(origobj));
    origobj = num.round(origobj);
    std::cout << "O " << origobj << std::endl;

    std::string pSol = "V ";
    if (status == PostsolveStatus::kOk) {
        std::string sign;
        for (int i = 0; i < origsol.primal.size(); i++) {
            if ((int)origsol.primal.at(i) == 0)
                sign = "-";
            else if ((int)origsol.primal.at(i) == 1)
                sign = "";
            else
                throw std::invalid_argument("ILLEGAL ORIGINAL SOLUTION: NON-BOOLEAN");

            pSol += sign + "x" + std::to_string(i + 1) + " ";
        }
    } else {
        throw std::invalid_argument("PaPILO POSTSOLVE FAILED");
    }

    // std::cout << pSol << std::endl;
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

template class MIPPreSolver<papilo::Rational>;

}  // namespace pre