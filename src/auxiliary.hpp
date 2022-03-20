#pragma once

#include <sys/resource.h>

#include <algorithm>
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
#include "typedef.hpp"

// most copied from rs
namespace pre {
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::pair<T, U>& p) {
    os << p.first << "," << p.second;
    return os;
}
template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<T, U>& m) {
    for (const auto& e : m) os << e << ";";
    return os;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& m) {
    for (const auto& e : m) os << e << " ";
    return os;
}

namespace aux {
template <typename T>
bigint sto_bigint(const std::string& s) {
    T answer = 0;
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
inline boost::multiprecision::int128_t abs(const boost::multiprecision::int128_t& x) {
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
inline boost::multiprecision::int128_t gcd(const boost::multiprecision::int128_t& x,
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
inline boost::multiprecision::int128_t lcm(const boost::multiprecision::int128_t& x,
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