#pragma once

#include "headFiles.hpp"
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
			} else if (s[0] == '*') {
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
			} else {
				infile >> varName;
				// std::cout << s << " " << varName << std::endl;
				builder.addEntry(row, varMap[varName], getCoeff(s));
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

	void collectResult() {
		std::string s = "";

		const papilo::ConstraintMatrix<T>& consmatrix = problem.getConstraintMatrix();
		const papilo::Vec<std::string>& varnames = problem.getVariableNames();
		const papilo::Vec<T>& lhs = consmatrix.getLeftHandSides();
		const papilo::Vec<papilo::RowFlags>& row_flags = problem.getRowFlags();
		const papilo::Vec<T>& rhs = consmatrix.getRightHandSides();

		s += "* #variable= " + std::to_string(consmatrix.getNCols())
		     + " #constraints= " + std::to_string(consmatrix.getNRows())
		     + "\n";

		// print objective
		s += "min: ";
		const papilo::Objective<T>objective = problem.getObjective();
		const papilo::Vec<T>objCoeff = objective.coefficients;
		for (int i = 0; i < objCoeff.size(); i++) {
			s += num2String(objCoeff[i]) + " " + varnames[i] + " ";
		}
		s += ";\n";

		// print constraint
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

	std::string num2String(T num) {
		std::string s = "";
		if (num < 0) {
			s += "-" + std::to_string(num);
		} else {
			s += "+" + std::to_string(num);
		}
		return s;
	}

	// PaPILO
	papilo::ProblemBuilder<T> builder;
	papilo::Problem<T> problem;
	papilo::Presolve<T> presolve;
	papilo::PresolveResult<T> result;
};

} // namespace pre
