#pragma once

// boost
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/program_options.hpp>
#include <boost/optional.hpp>
#include <boost/process.hpp>
#include <boost/asio.hpp>

// papilo
#include "papilo/core/ConstraintMatrix.hpp"
#include "papilo/core/postsolve/Postsolve.hpp"
#include "papilo/core/Presolve.hpp"
#include "papilo/core/Problem.hpp"
#include "papilo/core/ProblemBuilder.hpp"
#include "papilo/core/PresolveMethod.hpp"
#include "papilo/io/MpsParser.hpp"
#include "papilo/misc/MultiPrecision.hpp"
#include "papilo/misc/Vec.hpp"
#include "papilo/misc/Wrappers.hpp"
#include "catch/catch.hpp"

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