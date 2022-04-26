#pragma once

#include <boost/algorithm/string.hpp>

#include "auxiliary.hpp"
#include "typedef.hpp"

namespace pre {
template <typename REAL>
struct Expr {
   public:
    bool operator==(const Expr& b) const {
        return cols == b.cols && deg == b.deg;
    }
    Expr() {}
    Expr(const std::string& lhs, const std::string& rhs);

    void getVars();
    void getCoeffs();
    void print();
    void invert();
    void addition(const Expr& exp, const int& var);
    const REAL& getDeg() { return this->deg; }
    const std::unordered_map<int, REAL>& getCols() { return this->cols; }
    const std::string& toString();
    const std::string& toOrdString();

    std::size_t hashValue;

   private:
    std::unordered_map<int, REAL> cols;
    std::unordered_map<int, REAL> norCols;
    REAL deg;
    std::string stringView;
};

template <typename REAL>
std::size_t hash_value(Expr<REAL> const& b) {
    boost::hash<REAL> hasher;
    return hasher(b.hashValue);
}

template <typename REAL>
struct ExprPool {
   public:
    ExprPool() {}
    void addExpr(const Expr<REAL>& e) { exprs.insert(e); }
    void addObj(const Expr<REAL>& _obj) { this->obj = _obj; }
    void delateExpr(const int& idx);
    void setSize(const int& n, const int& m) { N = n, M = m; }
    const auto& getExprs() { return exprs; }
    void print() {
        obj.print();
        for (auto e : exprs) e.print();
    }

   private:
    std::unordered_set<Expr<REAL>, boost::hash<Expr<REAL>>> exprs;
    Expr<REAL> obj;
    int N;
    int M;
};

}  // namespace pre