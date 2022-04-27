#pragma once

#include <boost/algorithm/string.hpp>

#include "auxiliary.hpp"
#include "typedef.hpp"

namespace pre {
template <typename REAL>
struct Expr {
   public:
    bool operator==(const Expr& b) const {
        return hashValue == b.hashValue && cols == b.cols && deg == b.deg;
    }
    Expr() {}
    Expr(const std::string& lhs, const std::string& rhs);

    void invert();
    void negate();
    void addition(const Expr& exp, const int& var);
    void setHash(std::size_t& h) { this->hashValue = h; }

    void print() const;
    const int getVarsSize() const { return cols.size(); }
    const REAL& getDeg() const { return deg; }
    const std::unordered_map<int, REAL>& getCols() const { return cols; }
    const std::size_t getHash() const { return hashValue; }

    friend std::size_t hash_value(Expr<REAL> const& b) {
        std::size_t h = b.hashValue;
        return h;
    }

   private:
    std::unordered_map<int, REAL> cols;
    std::unordered_map<int, REAL> norCols;
    REAL deg;
    std::string stringView;
    std::size_t hashValue;
};

template <typename REAL>
struct ExprPool {
   public:
    ExprPool() {}
    void addExpr(Expr<REAL>& e) {
        e.setHash(++ghostCode);
        exprs.insert(e);
    }
    void addObj(Expr<REAL>& _obj) {
        _obj.setHash(++ghostCode);
        this->obj = _obj;
    }
    void delateExpr(const Expr<REAL>& e) { exprs.erase(e); }
    void setSize(const int& n, const int& m) { N = n, M = m; }
    auto& getExprs() { return exprs; }
    std::size_t& getGhostCode() { return this->ghostCode; }
    const int& getVarNum() { return N; }
    const int& getOrigConsNum() { return M; }
    int getCosNum() { return exprs.size(); }
    void print() {
        obj.print();
        for (auto e : exprs) e.print();
    }

   private:
    std::unordered_set<Expr<REAL>, boost::hash<Expr<REAL>>> exprs;
    Expr<REAL> obj;
    int N;
    int M;
    std::size_t ghostCode;
};

}  // namespace pre