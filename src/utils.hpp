#pragma once

// papilo
//! cannot add more headfile otherwise complie error
#include "papilo/core/Presolve.hpp"
#include "papilo/core/Problem.hpp"
#include "papilo/core/ProblemBuilder.hpp"
#include "papilo/core/postsolve/Postsolve.hpp"

// std
#include <ctype.h>
#include <stdio.h>

#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace pre {
namespace utils {

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type {
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

template <typename T>
void printAbstractProblem(papilo::Problem<T> prob);

template <typename T>
void printDetailedProblem(papilo::Problem<T> prob);

template <typename T>
void printVector(papilo::Vec<T> const& input);

}  // namespace utils
}  // namespace pre