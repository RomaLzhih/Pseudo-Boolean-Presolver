
#include "MIP.hpp"
#include <boost/algorithm/string.hpp>

namespace pre {

// main functionality
template <typename T>
void MIPPreSolver<T>::buildProblem(std::string inFileName) {
	std::cout << "hello world" << std::endl;
	std::cout << "hello world" << std::endl;

	std::ifstream infile(inFileName);
	std::string line;
	std::getline(infile, line);
	std::string colNumStr = line.substr(line.find_first_of("=") + 2);
	std::string rowNumStr = line.substr(line.find_last_of("=") + 2);
	int colNum = std::stoi(colNumStr.substr(0, colNumStr.find_first_of(" ")));
	int rowNum = std::stoi(rowNumStr);

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
			if (getCoeff(s) != 0) {  // papilo doesn't allow add zero entry
				builder.addEntry(row, varMap[varName], getCoeff(s));
			}
			// std::cout << s << " " << varName << std::endl;
		}
	}

	infile.close();
	problem = builder.build();
}

template <typename T>
void MIPPreSolver<T>::setPara() {
	std::string paraPath = "../parameters.opb.txt";
	std::ifstream infile(paraPath);
	std::cout << infile.is_open() << std::endl;

	std::string line;

	papilo::ParameterSet paramset = presolve.getParameters();

	while (std::getline(infile, line)) {
		if (line.empty() || line[0] == '#') continue;
		int pos = line.find_first_of("=");
		std::string para = line.substr(0, pos - 1);
		std::string val = line.substr(pos + 2);
		std::cout << para << " " << val << std::endl;
		paramset.parseParameter(para.c_str(), val.c_str());
	}

	infile.close();
	return;
}

template <typename T>
int MIPPreSolver<T>::runPresolve() {
	presolve.addDefaultPresolvers();
	setPara();
	result = presolve.apply(problem);
	std::cout << utils::as_integer(result.status) << std::endl;
	return (int) utils::as_integer(result.status);
}

template <typename T>
std::string MIPPreSolver<T>::collectResult() {

	std::string str = "";

	const papilo::ConstraintMatrix<T>& consmatrix = problem.getConstraintMatrix();
	const papilo::Vec<std::string>& varnames = problem.getVariableNames();
	const papilo::Objective<T>& objective = problem.getObjective();
	const papilo::Vec<papilo::ColFlags>& col_flags = problem.getColFlags();
	const papilo::Vec<papilo::RowFlags>& row_flags = problem.getRowFlags();
	const papilo::Vec<T>& lhs = consmatrix.getLeftHandSides();
	const papilo::Vec<T>& rhs = consmatrix.getRightHandSides();

	int nCols = consmatrix.getNCols();
	int nRows = consmatrix.getNRows();

	str += "* #variable= " + std::to_string(nCols) + " #constraint= " + std::to_string(nRows) + "\n";

	// print objective
	str += "min: ";
	const papilo::Vec<T> objCoeff = objective.coefficients;
	for (int i = 0; i < objCoeff.size(); i++) {
		str += signNum2StrDown(objCoeff[i]) + " " + varnames[i] + " ";
	}
	str += ";\n";

	// print constraint
	for (int i = 0; i < nRows; i++) {
		const papilo::SparseVectorView<T>& row = consmatrix.getRowCoefficients(i);

		const bool L = row_flags[i].test(papilo::RowFlag::kLhsInf) ? 1 : 0;
		const bool R = row_flags[i].test(papilo::RowFlag::kRhsInf) ? 1 : 0;

		if (!L && R) {  // a <= x
			str += writeConstraint(row, varnames, 1, ">=", lhs[i]);
		} else if (L && !R) {  // x <= b
			str += writeConstraint(row, varnames, -1, ">=", (T)(-1 * rhs[i]));
		} else if (!L && !R) {
			if (lhs[i] == rhs[i]) {  // a = x = b
				str += writeConstraint(row, varnames, 1, "=", lhs[i]);
			} else {  // a <= x <= b, a != b
				str += writeConstraint(row, varnames, 1, ">=", lhs[i]);
				str += writeConstraint(row, varnames, -1, ">=", (T)(-1 * rhs[i]));
			}
		} else {
			throw std::invalid_argument("Row " + std::to_string(i) + " contains invalid constraint. LhsInf: " + std::to_string(row_flags[i].test(papilo::RowFlag::kLhsInf)) + " RhsInf: " + std::to_string(row_flags[i].test(papilo::RowFlag::kRhsInf)));
		}
	}

	// std::cout << str << std::endl;

	return str;
}

template <typename T>
void MIPPreSolver<T>::postSolve(std::string& rsSol) {
	papilo::Vec<T> reducedsolvals;
	std::vector<std::string> sols;
	boost::split(sols, rsSol, boost::is_any_of(" "), boost::token_compress_on);
	for (auto s : sols) {
		if (s[0] == '+' || s[0] == 'x') reducedsolvals.push_back(1);
		else if (s[0] == '-') reducedsolvals.push_back(0);
		else throw std::invalid_argument("INVALID ROUNDINGSAT SOLUTION");
	}
	if (reducedsolvals.size() != problem.getConstraintMatrix().getNCols()) {
		throw std::invalid_argument("UNMACHED SOLUTION, REQUIRE: "
		                            + std::to_string(problem.getConstraintMatrix().getNCols())
		                            + " OBTAIN: " + std::to_string(reducedsolvals.size()));
	}

	const papilo::Num<double> num{};
	papilo::Message msg{};
	papilo::Postsolve<T> postsolve{msg, num};
	papilo::Solution<T> reducedsol(std::move(reducedsolvals));
	papilo::Solution<T> origsol;
	PostsolveStatus status = postsolve.undo(reducedsol, origsol, result.postsolve);

	if (status == PostsolveStatus::kOk) {
		std::string sign = "";
		for (int i = 0; i < origsol.primal.size(); i++) {
			if ((int)origsol.primal.at(i) == 0) sign = "-";
			else if ((int)origsol.primal.at(i) == 1) sign = "+";
			else throw std::invalid_argument("ILLEGAL ORIGINAL SOLUTION");

			std::cout << sign + "x" + std::to_string(i + 1) << " ";
		}
	} else {
		throw std::invalid_argument("PaPILO POSTSOLVE FAILED");
	}
	return;
}

// helper function
template <typename T>
T MIPPreSolver<T>::getCoeff(std::string s) {
	T num;
	if (std::isdigit(s[0])) {  // unsigned integer
		num = (T)std::stoi(s);
	} else if (s[0] == '+') {
		num = (T)std::stoi(s.substr(1));
	} else if (s[0] == '-') {
		num = (T)(-1 * std::stoi(s.substr(1)));
	}
	return num;
}

template <typename T>
std::string MIPPreSolver<T>::signNum2StrUp(T num) {
	std::string s = "";
	if (num < 0) {
		s = std::to_string((int)ceil(num));
	} else {
		s = "+" + std::to_string((int)ceil(num));
	}
	return s;
}

template <typename T>
std::string MIPPreSolver<T>::signNum2StrDown(T num) {
	std::string s = "";
	if (num < 0) {
		s = std::to_string((int)floor(num));
	} else {
		s = "+" + std::to_string((int)floor(num));
	}
	return s;
}

template <typename T>
std::string MIPPreSolver<T>::writeConstraint(const papilo::SparseVectorView<T>& row,
                const papilo::Vec<std::string>& varnames,
                int flip, std::string op, T deg) {
	const T* rowVals = row.getValues();
	const int* indices = row.getIndices();
	const auto len = row.getLength();
	std::string s = "";
	for (int j = 0; j < len; j++) {
		s += signNum2StrDown((T)(flip * rowVals[j])) + " " + varnames[indices[j]] + " ";
	}
	s += op + " " + signNum2StrUp(deg) + " ;\n";
	return s;
}

template class MIPPreSolver<double>;

}  // namespace pre