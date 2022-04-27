#pragma once

#include <sys/resource.h>

#include <algorithm>
#include <boost/container_hash/hash.hpp>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "papilo/misc/MultiPrecision.hpp"
#include "papilo/misc/Num.hpp"
#include "papilo/misc/VectorUtils.hpp"
#include "typedef.hpp"

// most copied from rs
namespace pre {
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
    os << p.first << " " << p.second << " ";
    return os;
}
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<T, U>& m) {
    for (const auto& e : m) os << e << ";" << std::endl;
    return os;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& m) {
    for (const auto& e : m) os << e << " ";
    return os;
}

namespace aux {
// Minisat cpuTime function
static inline double cpuTime() {
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    return (double)ru.ru_utime.tv_sec + (double)ru.ru_utime.tv_usec / 1000000;
}
template <typename T>
T sto(const std::string& s) {
    return std::stold(s);
}
template <>
inline double sto(const std::string& s) {
    return std::stod(s);
}
template <>
inline std::string sto(const std::string& s) {
    return s;
}

template <typename T>
inline std::string tos(const T& x) {
    bigint N(x);
    return N.str();
}
template <>
inline std::string tos(const bigint& x) {
    return x.str();
}
template <>
inline std::string tos(const int& x) {
    return std::to_string(x);
}
template <>
inline std::string tos(const long long& x) {
    return std::to_string(x);
}
template <typename T>
T mod_safe(const T& p, const T& q) {
    assert(q > 0);
    if (p < 0)
        return q - (-p % q);
    else
        return p % q;
}
template <typename T>
std::size_t hashExpr(const std::unordered_map<int, T>& cols, const T& deg) {
    auto fibonacci_muliplier = [&]() {
        return (std::size_t)(0x9e3779b97f4a7c15);
    };
    auto rotate_left = [&](unsigned long x, int n) {
        return (std::size_t)(x << n) | (x >> (64 - n));
    };
    auto addValue = [&](std::size_t& seed, T val) {
        seed = (std::size_t)(rotate_left(seed, 5) ^ T(val)) *
               fibonacci_muliplier();
    };

    std::size_t seed = 0;
    addValue(seed, (T)(aux::cpuTime() * 1e24));
    boost::hash_combine(seed, deg);

    return seed;
}

template <typename T>
std::string Expr2String(const std::unordered_map<int, T>& cols, const T& deg) {
    std::string stringView = "";
    for (auto c : cols) {
        stringView += (c.second > 0 ? "+" : "") + aux::tos(c.second) + " x" +
                      aux::tos(c.first) + " ";
    }
    stringView += ">= " + aux::tos(deg) + " ;";
    return stringView;
}

template <typename T>
std::string Expr2OrdString(const std::unordered_map<int, T>& cols,
                           const T& deg) {
    std::string stringView = "";
    auto key_selector = [](auto p) { return p.first; };
    std::vector<int> v(cols.size());
    std::transform(cols.begin(), cols.end(), v.begin(), key_selector);
    std::sort(v.begin(), v.end());
    for (auto i : v) {
        stringView += (cols.at(i) > 0 ? "+" : "") + aux::tos(cols.at(i)) +
                      " x" + aux::tos(i) + " ";
    }
    stringView += ">= " + aux::tos(deg) + " ;";
    return stringView;
}

template <typename T>
std::string Expr2NegString(const std::unordered_map<int, T>& cols,
                           const T& deg) {
    std::string stringView = "";
    for (auto c : cols) {
        stringView += (c.second < 0 ? "+" : "") + aux::tos(-c.second) + " x" +
                      aux::tos(c.first) + " ";
    }
    stringView += ">= " + aux::tos(-deg + 1) + " ;";
    return stringView;
}

template <typename T>
T min(const std::vector<T>& v) {
    return *std::min_element(v.begin(), v.end());
}

template <typename T>
T max(const std::vector<T>& v) {
    return *std::max_element(v.begin(), v.end());
}

template <typename T>
T abs(const T& x) {
    return std::abs(x);
}
template <>
inline papilo::Rational abs(const papilo::Rational& x) {
    return boost::multiprecision::abs(x);
}
template <>
inline bigint abs(const bigint& x) {
    return boost::multiprecision::abs(x);
}
template <>
inline boost::multiprecision::int128_t abs(
    const boost::multiprecision::int128_t& x) {
    return boost::multiprecision::abs(x);
}

// GCD
template <typename T>
T gcd(const T& x, const T& y) {
    return std::gcd(x, y);
}
template <>
inline bigint gcd(const bigint& x, const bigint& y) {
    return boost::multiprecision::gcd(x, y);
}
template <>
inline boost::multiprecision::int128_t gcd(
    const boost::multiprecision::int128_t& x,
    const boost::multiprecision::int128_t& y) {
    return boost::multiprecision::gcd(x, y);
}

// LCM
template <typename T>
T lcm(const T& x, const T& y) {
    return std::lcm(x, y);
}
template <>
inline bigint lcm(const bigint& x, const bigint& y) {
    return boost::multiprecision::lcm(x, y);
}
template <>
inline boost::multiprecision::int128_t lcm(
    const boost::multiprecision::int128_t& x,
    const boost::multiprecision::int128_t& y) {
    return boost::multiprecision::lcm(x, y);
}

// numerator and denominator
// do not accept irrational type
template <typename T>
inline bigint numerator(const T& x) {
    return (bigint)boost::multiprecision::numerator(x);
}
template <typename T>
inline bigint denominator(const T& x) {
    return (bigint)boost::multiprecision::denominator(x);
}

}  // namespace aux

}  // namespace pre