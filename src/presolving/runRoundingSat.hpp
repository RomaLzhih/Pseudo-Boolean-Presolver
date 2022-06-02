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

#include "presolving/auxiliary.hpp"
#include "presolving/typedef.hpp"

namespace pre
{
namespace runRoundingSat
{
void
runRS( std::string& infile );
strpair // run presolved ins
runforPaPILO( std::string& preInfo, std::string infile, double& time );
strpair // run initial ins
runforPaPILO( const std::string& infile, double& time );
std::string
runforRedundancy( std::string& preInfo, std::string infile );
strpair // run presolved ins
runforSAT( const std::string& preInfo, std::string& infile, double& time );
strpair // run initial ins
runforSAT( const std::string& infile, double& time );

} // namespace runRoundingSat
} // namespace pre