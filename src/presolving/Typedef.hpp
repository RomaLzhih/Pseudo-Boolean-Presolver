#pragma once

#include <cstring>
#include <iostream>
#include <utility>

#include "boost/multiprecision/cpp_int.hpp"

namespace pre {
enum class fileType : int {
    opt = 1 << 0,
    dec = 1 << 1
};

enum class solStat : int {
    UNSATISFIABLE = 1 << 0,
    SATISFIABLE = 1 << 1,
    OPTIMAL = 1<< 2
};

using bigint = boost::multiprecision::cpp_int;
using strpair = std::pair<std::string, std::string>;

}  // namespace pre