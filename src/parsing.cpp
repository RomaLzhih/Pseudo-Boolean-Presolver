#include "parsing.hpp"

namespace pre {
namespace parser {
papilo::Rational read_number(const std::string& s) {
    papilo::Rational answer = 0;
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
fileType opb_read_to_papilo(std::ifstream& infile,
                            papilo::ProblemBuilder<REAL>& builder) {
    std::string line;
    std::getline(infile, line);
    std::string colNumStr = line.substr(line.find_first_of("=") + 2);
    std::string rowNumStr = line.substr(line.find_last_of("=") + 2);
    int colNum = std::stoi(colNumStr.substr(0, colNumStr.find_first_of(" ")));
    int rowNum =
        std::stoi(rowNumStr);  //! papilo supports only int number of variables

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
    std::string varName = "";
    fileType f;
    while (std::getline(infile, line)) {
        if (line.empty() || line[0] == '*')
            continue;
        else if (line.substr(0, 4) == "min:") {
            std::istringstream is(line.substr(5));
            while (is >> s) {
                if (s == ";") break;
                is >> varName;
                builder.setObj(varMap[varName], read_number(s));
            }
            f = fileType::opt;
            std::getline(infile, line);  // opt case, get first constraint
            assert(line.find(">=") || line.find("="));
            break;
        } else if (line.find(">=") ||
                   line.find("=")) {  // dec case's first constraint
            papilo::Vec<REAL> v(colNum, 0);
            builder.setObjAll(v);
            f = fileType::dec;
            break;
        }
    }
    // add constraint
    int row = 0;
    std::string RHS;
    do {
        if (line.empty() || line[0] == '*') continue;
        std::istringstream is(line);
        while (is >> s) {
            if (s == ">=") {
                is >> RHS;
                builder.setRowLhsInf(row, false);
                builder.setRowRhsInf(row, true);
                builder.setRowLhs(row, read_number(RHS));
            } else if (s == "=") {
                is >> RHS;
                builder.setRowLhsInf(row, false);
                builder.setRowRhsInf(row, false);
                builder.setRowLhs(row, read_number(RHS));
                builder.setRowRhs(row, read_number(RHS));
            } else if (s == ";") {
                row++;
                // std::cout << "row: " << row << std::endl;
            } else {
                is >> varName;
                if (read_number(s) != (REAL)0) {
                    // papilo doesn't allow add zero entry
                    builder.addEntry(row, varMap[varName], read_number(s));
                }
                // std::cout << s << " " << varName << std::endl;
            }
        }
    } while (std::getline(infile, line));
    return f;
}

template <typename REAL>
fileType opb_read_to_sat(std::ifstream& infile, ExprPool<REAL>& exprs) {
    std::string line;
    std::getline(infile, line);
    std::string colNumStr = line.substr(line.find_first_of("=") + 2);
    std::string rowNumStr = line.substr(line.find_last_of("=") + 2);
    int colNum = std::stoi(colNumStr.substr(0, colNumStr.find_first_of(" ")));
    int origRowNum = std::stoi(rowNumStr);
    exprs.setSize(colNum, origRowNum);

    fileType f;
    std::string lhs, rhs;
    while (std::getline(infile, line)) {
        if (line.empty() || line[0] == '*')
            continue;
        else if (line.substr(0, 4) == "min:") {
            lhs = line.substr(5), lhs.pop_back(), lhs.pop_back();
            rhs = "";
            Expr<REAL> e(lhs, rhs);
            exprs.addObj(e);
            f = fileType::opt;
            std::getline(infile, line);  // opt case, get first constraint
            assert(line.find(">=") || line.find("="));
            break;
        } else if (line.find(">=") ||
                   line.find("=")) {  // dec case's first constraint
            f = fileType::dec;
            break;
        }
    }

    int op;
    int eq = 0, less = 0;
    std::set<REAL> s;
    do {
        if (line.empty() || line[0] == '*') continue;
        op = line.find(">=") == std::string::npos ? line.find("=")
                                                  : line.find(">=");
        lhs = line.substr(0, op - 1);
        rhs = line[op] == '>' ? line.substr(op + 3) : line.substr(op + 2);
        assert(*rhs.rbegin() == ';');
        rhs.pop_back(), rhs.pop_back();  // pop away ; and " "
        Expr<REAL> e(lhs, rhs);
        exprs.addExpr(e);
        if (line[op] == '=') {
            e.invert();
            exprs.addExpr(e);
            eq++;
        } else {
            less++;
        }
    } while (std::getline(infile, line));
    assert(exprs.getExprs().size() == less + eq * 2);  // no collision
    assert(exprs.getGhostCode()-1 == exprs.getExprs().size());
    return f;
}

template fileType opb_read_to_sat<bigint>(std::ifstream& infile,
                                          ExprPool<bigint>& exprs);
template fileType opb_read_to_papilo<papilo::Rational>(
    std::ifstream& infile, papilo::ProblemBuilder<papilo::Rational>& builder);

}  // namespace parser
}  // namespace pre