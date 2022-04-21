
#include "presolving/MIP.hpp"
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
void MIPPreSolver<REAL>::buildProblem(const std::string& inFileName) {
  std::ifstream infile(inFileName);
  assert(!infile.fail());
  this->inputIns = inFileName;

  this->instanceType = parser::opb_read(infile, builder) ? fileType::opt : fileType::dec;

  infile.close();
  this->problem = builder.build();
  return;
}

template <typename REAL>
int MIPPreSolver<REAL>::runPresolve() {
  auto setPara = [&]() {
    std::string paraPath = "../param/parameters.test.txt";
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

  this->presolve.addDefaultPresolvers();
  setPara();
  this->result = presolve.apply(problem);

  this->num.setEpsilon(presolve.getEpsilon());  // use same tollerance with papilo
  this->num.setFeasTol(presolve.getFeasTol());
  this->num.setHugeVal(presolve.getHugeVal());

  if (this->problem.getNCols() == 0)
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
  if (result.postsolve.postsolveType == PostsolveType::kFull) empty_sol.type = papilo::SolutionType::kPrimalDual;

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
      throw std::invalid_argument("Row " + std::to_string(i) + " contains invalid constraint. LhsInf: " +
                                  std::to_string(row_flags[i].test(papilo::RowFlag::kLhsInf)) +
                                  " RhsInf: " + std::to_string(row_flags[i].test(papilo::RowFlag::kRhsInf)));
    }
  }

  return str;
}

template <typename REAL>  // rsStatus and rsSol
void MIPPreSolver<REAL>::postSolve(const std::vector<int>& rsSol, const pre::solStat& rsStat) {
  if (rsStat == solStat::UNSATISFIABLE) {
    this->solutionStatus = solStat::UNSATISFIABLE;
    return;
  }
  assert(rsStat == solStat::OPTIMAL || rsStat == solStat::SATISFIABLE);
  assert(rsSol.size());

  papilo::Vec<REAL> reducedsolvals;
  for (auto s : rsSol) reducedsolvals.push_back(s);

  if (reducedsolvals.size() != problem.getConstraintMatrix().getNCols()) {
    throw std::invalid_argument(
        "UNMACHED SOLUTION, REQUIRE: " + std::to_string(problem.getConstraintMatrix().getNCols()) +
        " OBTAIN: " + std::to_string(reducedsolvals.size()));
  }

  papilo::Message msg{};
  papilo::Postsolve<REAL> postsolve{msg, num};
  papilo::Solution<REAL> reducedsol(std::move(reducedsolvals));
  papilo::Solution<REAL> origsol;
  PostsolveStatus status = postsolve.undo(reducedsol, origsol, result.postsolve);

  this->origobj = result.postsolve.getOriginalProblem().computeSolObjective(origsol.primal);
  assert(num.isIntegral(origobj));
  this->origobj = num.round(origobj);  // round to integer

  if (status == PostsolveStatus::kOk) {
    this->sol = origsol.primal;
    this->solutionStatus = solStat::SATISFIABLE;
  } else {
    throw std::invalid_argument("PaPILO POSTSOLVE FAILED");
  }

  return;
}

// helper function
template <typename REAL>
std::string MIPPreSolver<REAL>::writeConstraint(const papilo::SparseVectorView<REAL>& row,
                                                const papilo::Vec<std::string>& varnames, const int& flip,
                                                const std::string& op, const REAL& deg) {
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

template <typename REAL>
void MIPPreSolver<REAL>::writePresolvers(const std::string& inFileName) {
  std::string inpath = "../param/printPresolveNames.txt";
  std::string outpath = inFileName.substr(0, inFileName.find_last_of("//") + 1) + "0-paraDoc.txt";
  std::ifstream infile(inpath);
  std::ofstream outfile(outpath, std::ios::app);
  outfile.setf(std::ios::left, std::ios::adjustfield);

  assert(!infile.fail());
  assert(!outfile.fail());
  outfile << inFileName.substr(inFileName.find_last_of("//") + 1) + '\n';

  std::string line;
  std::unordered_set<std::string> presolverNames;
  bool BYNCALLS;
  while (getline(infile, line)) {
    if (line.empty())
      continue;
    else if (line[0] == '!' && line[2] == 'T')
      BYNCALLS = *line.rbegin() == '0' ? false : true;
    else if (*line.rbegin() != '*')
      presolverNames.insert(line);
  }

  papilo::Message msg{};
  papilo::Vec<std::pair<int, int>> presolverStats = presolve.getPresolverStats();
  std::string name;
  unsigned int ncalls;
  unsigned int nsuccessCall;
  double execTime;

  for (std::size_t i = 0; i < presolve.getPresolvers().size(); ++i) {
    name = presolve.getPresolvers()[i]->getName();
    ncalls = presolve.getPresolvers()[i]->getNCalls();
    nsuccessCall = presolve.getPresolvers()[i]->getNSuccessCalls();
    execTime = presolve.getPresolvers()[i]->getExecTime();
    std::pair<int, int> stats = presolverStats[i];

    if (presolverNames.count(name)) {
      if ((!BYNCALLS && ncalls) || (BYNCALLS && nsuccessCall)) {
        // presolve.getPresolvers()[i]->printStats(msg, presolverStats[i]);
        double success = ncalls == 0 ? 0.0 : (double(nsuccessCall) / double(ncalls)) * 100.0;
        double applied = stats.first == 0 ? 0.0 : (double(stats.second) / double(stats.first)) * 100.0;

        outfile << '\t';
        outfile << std::setw(16) << name;
        outfile << std::setw(16) << ncalls;
        outfile << std::setw(16) << success;
        outfile << std::setw(16) << stats.first;
        outfile << std::setw(16) << applied;
        outfile << std::setw(16) << std::round(execTime * 10000) / 10000;
        outfile << '\n';
      }
    }
  }
  outfile << std::endl;

  outfile.close();
  infile.close();
  return;
}

template class MIPPreSolver<papilo::Rational>;

}  // namespace pre