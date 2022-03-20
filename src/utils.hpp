#pragma once

// papilo
//! cannot add more headfile otherwise complie error
#include "papilo/core/Presolve.hpp"
#include "papilo/core/Problem.hpp"
#include "papilo/core/ProblemBuilder.hpp"
#include "papilo/core/postsolve/Postsolve.hpp"

// std
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>

// pre
#include "auxiliary.hpp"

namespace pre {
namespace utils {

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type {
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

template <typename REAL>
void printAbstractProblem(papilo::Problem<REAL> prob);

template <typename REAL>
void printDetailedProblem(papilo::Problem<REAL> prob);

template <typename REAL>
void printVector(papilo::Vec<REAL> const& input);

}  // namespace utils
}  // namespace pre