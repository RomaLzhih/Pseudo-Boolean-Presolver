#pragma once

#include "utils.hpp"

namespace pre {

template <typename T>
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
	void buildProblem(std::string inFileName);

	void setPara();

	void runPresolve();

	std::string collectResult();

	// helper function
	T getCoeff(std::string s);

	std::string signNum2StrUp(T num);

	std::string signNum2StrDown(T num);

	std::string writeConstraint(const papilo::SparseVectorView<T>& row,
	                            const papilo::Vec<std::string>& varnames,
	                            int flip, std::string op, T deg);
private:
// PaPILO
	papilo::ProblemBuilder<T> builder;
	papilo::Problem<T> problem;
	papilo::Presolve<T> presolve;
	papilo::PresolveResult<T> result;
};

}  // namespace pre
