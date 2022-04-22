#pragma once

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <boost/process.hpp>
#include <boost/program_options.hpp>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include "presolving/Typedef.hpp"

namespace rs{
namespace pre {
namespace runRoundingSat {

std::string getMIPSolvedFile(const std::string& preInfo, std::string infile);

}  // namespace runRoundingSat
}  // namespace pre
} // rs