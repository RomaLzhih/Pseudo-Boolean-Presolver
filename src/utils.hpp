#pragma once

// papilo
//! cannot add more headfile otherwise complie error
#include "papilo/core/postsolve/Postsolve.hpp"
#include "papilo/core/Presolve.hpp"
#include "papilo/core/Problem.hpp"
#include "papilo/core/ProblemBuilder.hpp"

// std
#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <stdio.h>
#include <ctype.h>
#include <cstdio>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <cmath>

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