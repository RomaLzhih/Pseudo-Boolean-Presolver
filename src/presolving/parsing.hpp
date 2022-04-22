#pragma once

#include "presolving/utils.hpp"

namespace rs{
namespace pre {
namespace parser {

papilo::Rational read_number(const std::string& s);

template <typename REAL>
int opb_read(std::ifstream& infile, papilo::ProblemBuilder<REAL>& builder);
}  // namespace parser
}  // namespace pre
}