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

namespace pre {
namespace runRoundingSat {

int run(std::string& info);

}// namespace runRoundingSat
}// namespace pre