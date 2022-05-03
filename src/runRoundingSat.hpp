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

#include "typedef.hpp"

namespace pre
{
namespace runRoundingSat
{
strpair
runforPaPILO( std::string& preInfo, std::string infile );
strpair
runforPaPILO( const std::string& infile );
std::string
runforRedundancy( std::string& preInfo, std::string infile );
strpair
runforSAT( const std::string& preInfo );
} // namespace runRoundingSat
} // namespace pre