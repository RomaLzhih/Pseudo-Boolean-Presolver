#pragma once

#include "papilo/core/ConstraintMatrix.hpp"
#include "papilo/core/postsolve/Postsolve.hpp"
#include "papilo/core/Presolve.hpp"
#include "papilo/core/Problem.hpp"
#include "papilo/core/ProblemBuilder.hpp"
#include "papilo/core/PresolveMethod.hpp"
#include "papilo/io/MpsParser.hpp"
#include "papilo/misc/MultiPrecision.hpp"
#include "papilo/misc/Vec.hpp"
#include "papilo/misc/Wrappers.hpp"
#include "catch/catch.hpp"

#include "utils.hpp"

namespace pre {
template<typename T>
class MIPPreSolver {
public:
	// export
	papilo::Problem<T> getOriginalProblem() {
		return problem;
	}

	void printAbstractProblem() {
		utils::printAbstractProblem(problem);
	}

	void printDetailedProblem() {
		utils::printDetailedProblem(problem);
	}

	// main functionality
	void buildProblem(std::string inFileName) {
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
			if (s.empty()) continue;
			else if (s[0] == '*') std::getline(infile, line);
			else break; // catch 'min:'
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
			} else if (s[0] == '*') { // TODO: add zeroOrMoreSpace
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
				if (getCoeff(s) != 0) { // papilo doesn't allow add zero entry
					builder.addEntry(row, varMap[varName], getCoeff(s));
				}
				// std::cout << s << " " << varName << std::endl;
			}
		}

		infile.close();
		problem = builder.build();
	}

	void runPresolve() {
		presolve.addDefaultPresolvers();
		result = presolve.apply(problem);
		std::cout << utils::as_integer(result.status) << std::endl;
		// TODO: add information for already solving
	}

	std::string collectResult() {
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

		str += "* #variable= " + std::to_string(nCols)
		       + " #constraint= " + std::to_string(nRows)
		       + "\n";

		// print objective
		str += "min: ";
		const papilo::Vec<T>objCoeff = objective.coefficients;
		for (int i = 0; i < objCoeff.size(); i++) {
			str += signNum2StrDown(objCoeff[i]) + " " + varnames[i] + " ";
		}
		str += ";\n";

		// print constraint
		for (int i = 0; i < nRows; i++) {
			const papilo::SparseVectorView<T>& row = consmatrix.getRowCoefficients(i);

			const bool L = row_flags[i].test( papilo::RowFlag::kLhsInf) ? 1 : 0;
			const bool R = row_flags[i].test( papilo::RowFlag::kRhsInf) ? 1 : 0;

			if (!L && R) { // a <= x
				str += writeConstraint(row, varnames, 1, ">=", lhs[i]);
			} else if (L && !R) {// x <= b
				str += writeConstraint(row, varnames, -1, ">=", (T)(-1 * rhs[i]));
			} else if (!L && !R) {
				if (lhs[i] == rhs[i]) { // a = x = b
					str += writeConstraint(row, varnames, 1, "=", lhs[i]);
				} else { // a <= x <= b, a != b
					str += writeConstraint(row, varnames, 1, ">=", lhs[i]);
					str += writeConstraint(row, varnames, -1, ">=", (T)(-1 * rhs[i]));
				}
			} else {
				throw std::invalid_argument( "Row " + std::to_string(i)
				                             + " contains invalid constraint. LhsInf: "
				                             + std::to_string(row_flags[i].test( papilo::RowFlag::kLhsInf))
				                             + " RhsInf: "
				                             + std::to_string(row_flags[i].test( papilo::RowFlag::kRhsInf)));
			}
		}

		//std::cout << str << std::endl;

		return str + "END_OF_PRESOLVE\n";
	}

private:

	T getCoeff(std::string s) {
		T num;
		if (std::isdigit(s[0])) {//unsigned integer
			num = (T)std::stoi(s);
		} else if (s[0] == '+') {
			num = (T)std::stoi(s.substr(1));
		} else if (s[0] == '-') {
			num = (T)(-1 * std::stoi(s.substr(1)));
		}
		return num;
	}

	std::string signNum2StrUp(T num) {
		std::string s = "";
		if (num < 0) {
			s = std::to_string((int)ceil(num));
		} else {
			s = "+" + std::to_string((int)ceil(num));
		}
		return s;
	}

	std::string signNum2StrDown(T num) {
		std::string s = "";
		if (num < 0) {
			s = std::to_string((int)floor(num));
		} else {
			s = "+" + std::to_string((int)floor(num));
		}
		return s;
	}

	std::string writeConstraint(const papilo::SparseVectorView<T> & row,
	                            const papilo::Vec<std::string>& varnames,
	                            int flip, std::string op, T deg) {
		const T* rowVals = row.getValues();
		const int* indices = row.getIndices();
		const auto len = row.getLength();
		std::string s = "";
		for ( int j = 0; j < len; j++) {
			s += signNum2StrDown((T)(flip * rowVals[j])) + " " + varnames[indices[j]] + " ";
		}
		s += op + " " + signNum2StrUp(deg) + " ;\n";
		return s;
	}

	// PaPILO
	papilo::ProblemBuilder<T> builder;
	papilo::Problem<T> problem;
	papilo::Presolve<T> presolve;
	papilo::PresolveResult<T> result;
};

} // namespace pre
