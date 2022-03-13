
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
    assert(infile.fail());

    std::string line;
    std::getline(infile, line);
    std::string colNumStr = line.substr(line.find_first_of("=") + 2);
    std::string rowNumStr = line.substr(line.find_last_of("=") + 2);
    int colNum = std::stoi(colNumStr.substr(0, colNumStr.find_first_of(" ")));
    int rowNum = std::stoi(rowNumStr);  //* papilo supports only int number of variables

    std::unordered_map<std::string, int> varMap;

    builder.setNumCols(colNum);
    builder.setNumRows(rowNum);
    // no need to set all since papilo add one-by-one as well
    for (int i = 0; i < colNum; i++) {
        std::string varName = "x" + std::to_string(i + 1);
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

    int coeff;
    std::string varName = "";

    // build objective
    while (infile >> s) {
        if (s == ";") {
            break;
        }
        infile >> varName;
        // std::cout << getCoeff(s) << std::endl;
        builder.setObj(varMap[varName], getCoeff(s));
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
            builder.setRowLhs(row, getCoeff(RHS));
        } else if (s == "=") {
            infile >> RHS;
            builder.setRowLhsInf(row, false);
            builder.setRowRhsInf(row, false);
            builder.setRowLhs(row, getCoeff(RHS));
            builder.setRowRhs(row, getCoeff(RHS));
        } else if (s == ";") {
            row++;
            // std::cout << "row: " << row << std::endl;
        } else {
            infile >> varName;
            if (getCoeff(s) != 0) {  // papilo doesn'REAL allow add zero entry
                builder.addEntry(row, varMap[varName], getCoeff(s));
            }
            // std::cout << s << " " << varName << std::endl;
        }
    }

    infile.close();
    problem = builder.build();
}

template <typename REAL>
void MIPPreSolver<REAL>::setPara() {
    std::string paraPath = "../parameters.test.txt";
    std::ifstream infile(paraPath);
    assert(infile.fail());

    std::string line;
    papilo::ParameterSet paramset = presolve.getParameters();
    while (std::getline(infile, line)) {
        if (line.empty() || line[0] == '#') continue;
        int pos = line.find_first_of("=");
        std::string para = line.substr(0, pos - 1);
        std::string val = line.substr(pos + 2);
        // std::cout << para << " " << val << std::endl;
        paramset.parseParameter(para.c_str(), val.c_str());
    }
    infile.close();
    return;
}

template <typename REAL>
int MIPPreSolver<REAL>::runPresolve() {
    presolve.addDefaultPresolvers();
    setPara();
    result = presolve.apply(problem);
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

    const papilo::Num<REAL> num{};
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
    const papilo::Num<REAL> num{};

    const papilo::ConstraintMatrix<REAL>& consmatrix = problem.getConstraintMatrix();
    const papilo::Vec<std::string>& varnames = problem.getVariableNames();
    const papilo::Objective<REAL>& objective = problem.getObjective();
    const papilo::Vec<papilo::ColFlags>& col_flags = problem.getColFlags();
    const papilo::Vec<papilo::RowFlags>& row_flags = problem.getRowFlags();
    const papilo::Vec<REAL>& lhs = consmatrix.getLeftHandSides();
    const papilo::Vec<REAL>& rhs = consmatrix.getRightHandSides();

    int nCols = consmatrix.getNCols();
    int nRows = consmatrix.getNRows();

    str += "* #variable= " + std::to_string(nCols) + " #constraint= " + std::to_string(nRows) + "\n";

    // print objective
    str += "min: ";
    const papilo::Vec<REAL> objCoeff = objective.coefficients;
    for (int i = 0; i < objCoeff.size(); i++) {
        if (num.isZero(objCoeff[i])) continue;
        assert(!num.isIntegral(objCoef[i]));
        str += tos(objCoeff[i]) + " " + varnames[i] + " ";
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
                str += writeConstraint(row, varnames, 1, "=", lhs[i]);
            } else {  // a <= x <= b, a != b
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

    const papilo::Num<REAL> num{};
    papilo::Message msg{};
    papilo::Postsolve<REAL> postsolve{msg, num};
    papilo::Solution<REAL> reducedsol(std::move(reducedsolvals));
    papilo::Solution<REAL> origsol;
    PostsolveStatus status = postsolve.undo(reducedsol, origsol, result.postsolve);

    std::cout << std::fixed << "O "
              << result.postsolve.getOriginalProblem().computeSolObjective(origsol.primal)
              << std::endl;

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

    std::cout << pSol << std::endl;
    return;
}

// helper function
template <typename REAL>
REAL MIPPreSolver<REAL>::getCoeff(const std::string& s) {
    REAL answer = 0;
    bool negate = false;
    for (char c : s) {
        if ('0' <= c && c <= '9') {
            answer *= 10;
            answer += c - '0';
        }
        negate = (negate || (c == '-'));
    }
    return negate ? -answer : answer;
}

template <typename REAL>
std::string MIPPreSolver<REAL>::tos(const REAL& num) {
    bigint N(num);
    return N.str();
}

template <typename REAL>
std::string MIPPreSolver<REAL>::writeConstraint(const papilo::SparseVectorView<REAL>& row,
                                                const papilo::Vec<std::string>& varnames,
                                                int flip, std::string op, REAL deg) {
    const REAL* rowVals = row.getValues();
    const int* indices = row.getIndices();
    const auto len = row.getLength();
    std::string s = "";
    for (int j = 0; j < len; j++) {
        s += tos((REAL)(flip * rowVals[j])) + " " + varnames[indices[j]] + " ";
    }
    s += op + " " + tos(deg) + " ;\n";
    return s;
}

template class MIPPreSolver<double>;
template class MIPPreSolver<papilo::Rational>;

}  // namespace pre