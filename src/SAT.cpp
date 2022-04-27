#include "SAT.hpp"

namespace pre {
template <typename REAL>
void SATPreSolver<REAL>::buildProblem(const std::string& inFileName) {
    std::ifstream infile(inFileName);
    assert(!infile.fail());
    this->inputIns = inFileName;
    this->instanceType = parser::opb_read_to_sat(infile, this->exprs);
    // this->exprs.print();

    infile.close();
}

template <typename REAL>
void SATPreSolver<REAL>::redundancyDetection() {
    //* check every pair of constraint using roundingSat
    //* D implies C means D and neg C unsat, discard C then
    std::string rsStat;
    auto es = this->exprs.getExprs();
    auto D = es.begin();
    auto C = es.begin();

    while (D != es.end()) {
        C = es.begin();
        while (C != es.end()) {
            if (C == D || (C->getVarsSize() > this->redCmpSize &&
                           D->getVarsSize() > this->redCmpSize)) {
                C++;
                continue;
            }
            std::string preInfo =
                "* #variable= " + aux::tos(this->exprs.getVarNum()) +
                " #constraint= 2 \n" +
                aux::Expr2String(D->getCols(), D->getDeg()) + '\n' +
                aux::Expr2NegString(C->getCols(), C->getDeg());

            // std::cout << preInfo << std::endl
            //           << aux::Expr2String(C->getCols(), C->getDeg())
            //           << std::endl;

            rsStat = pre::runRoundingSat::runforSAT(preInfo, this->inputIns);

            auto tmp = C;
            tmp++;
            if (rsStat == "UNSATISFIABLE") {
                this->redRelation.push_back(std::make_pair(*D, *C));
                es.erase(C);
                this->redDelNum++;
            } else {
                assert(rsStat == "SATISFIABLE" || rsStat == "OPTIMUM");
            }
            C = tmp;
            this->redCallNum++;
        }
        D++;
    }

    // for (int i = 0; i < redRelation.size(); i++) {
    //     redRelation[i].first.print();
    //     std::cout << "|= ";
    //     redRelation[i].second.print();
    //     std::cout << "Neg: "
    //               << aux::Expr2NegString(redRelation[i].second.getCols(),
    //                                      redRelation[i].second.getDeg())
    //               << std::endl;
    //     std::cout << std::endl;
    // }

    return;
}

template <typename REAL>
void SATPreSolver<REAL>::writePresolvers(const std::string& inFileName) {
    std::string inpath = "../param/printPresolveNames.txt";
    std::string outpath =
        inFileName.substr(0, inFileName.find_last_of("//") + 1) +
        "0-paraDoc.txt";
    std::ifstream infile(inpath);
    std::ofstream outfile(outpath, std::ios::app);
    outfile.setf(std::ios::left, std::ios::adjustfield);

    assert(!infile.fail());
    assert(!outfile.fail());
    outfile << inFileName.substr(inFileName.find_last_of("//") + 1) + '\n';
    outfile << '\t' << this->redCallNum << " " << this->redDelNum << std::endl;
    outfile << std::endl;

    outfile.close();
    infile.close();
    return;
}
template class SATPreSolver<bigint>;
}  // namespace pre