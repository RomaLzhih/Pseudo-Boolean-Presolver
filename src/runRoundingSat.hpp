#pragma once

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/program_options.hpp>
#include <boost/optional.hpp>
#include <boost/process.hpp>
#include <boost/asio.hpp>

#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>

#include "typedef.hpp"

namespace pre {
namespace runRoundingSat {
strpair runforPaPILO(std::string& preInfo, std::string infile);
std::string runforSAT(std::string& preInfo, std::string infile);
}// namespace runRoundingSat
}// namespace pre