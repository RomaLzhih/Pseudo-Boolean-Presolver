#pragma once

#include "presolving/Constr.hpp"
#include "presolving/utils.hpp"

namespace pre {
namespace parser {

papilo::Rational read_number(const std::string& s);

template <typename REAL>
fileType opb_read_to_papilo(std::ifstream& infile, papilo::ProblemBuilder<REAL>& builder);

template <typename REAL>
fileType opb_read_to_sat(std::ifstream& infile, ExprPool<REAL>& exprs);
}  // namespace parser
}  // namespace pre        