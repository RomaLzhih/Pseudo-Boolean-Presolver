# Install script for directory: /mnt/d/aMain/4-pre/pre/papilo

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/papilo" TYPE FILE FILES
    "/mnt/d/aMain/4-pre/pre/build/papilo/papilo/CMakeConfig.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/Config.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/papilo" TYPE FILE FILES "/mnt/d/aMain/4-pre/pre/build/papilo-config-version.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/papilo/core" TYPE FILE FILES
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/Components.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/ConstraintMatrix.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/MatrixBuffer.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/Objective.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/Presolve.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/PresolveMethod.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/PresolveOptions.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/ProbingView.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/Problem.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/ProblemBuilder.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/ProblemUpdate.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/Reductions.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/RowFlags.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/SingleRow.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/Solution.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/SparseStorage.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/Statistics.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/VariableDomains.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/papilo/core/postsolve" TYPE FILE FILES
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/postsolve/BoundStorage.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/postsolve/PostsolveStorage.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/postsolve/Postsolve.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/postsolve/PostsolveStatus.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/postsolve/PostsolveType.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/postsolve/ReductionType.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/core/postsolve/SavedRow.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/papilo/interfaces" TYPE FILE FILES
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/interfaces/HighsInterface.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/interfaces/ScipInterface.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/interfaces/SolverInterface.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/interfaces/SoplexInterface.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/papilo/io" TYPE FILE FILES
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/io/Message.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/io/MpsParser.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/io/MpsWriter.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/io/SolParser.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/io/SolWriter.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/papilo/misc" TYPE FILE FILES
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/Alloc.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/Array.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/compress_vector.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/DependentRows.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/Flags.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/tbb.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/fmt.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/Hash.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/MultiPrecision.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/Num.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/NumericalStatistics.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/PrimalDualSolValidation.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/OptionsParser.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/VersionLogger.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/ParameterSet.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/Signature.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/StableSum.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/String.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/Timer.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/Validation.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/Vec.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/VectorUtils.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/misc/Wrappers.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/papilo/presolvers" TYPE FILE FILES
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/CoefficientStrengthening.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/ConstraintPropagation.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/DominatedCols.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/DualFix.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/DualInfer.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/FixContinuous.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/FreeVarSubstitution.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/ImplIntDetection.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/ParallelColDetection.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/ParallelRowDetection.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/Probing.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/SimpleProbing.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/SimpleSubstitution.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/SimplifyInequalities.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/SingletonCols.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/SingletonStuffing.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/src/papilo/presolvers/Sparsify.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/papilo-external/fmt" TYPE FILE FILES
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/chrono.h"
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/color.h"
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/compile.h"
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/core.h"
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/format.h"
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/format-inl.h"
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/locale.h"
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/ostream.h"
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/posix.h"
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/printf.h"
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/ranges.h"
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/format.cc"
    "/mnt/d/aMain/4-pre/pre/papilo/external/fmt/posix.cc"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/papilo-external/pdqsort" TYPE FILE FILES "/mnt/d/aMain/4-pre/pre/papilo/external/pdqsort/pdqsort.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/papilo-external/ska" TYPE FILE FILES
    "/mnt/d/aMain/4-pre/pre/papilo/external/ska/bytell_hash_map.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/external/ska/flat_hash_map.hpp"
    "/mnt/d/aMain/4-pre/pre/papilo/external/ska/unordered_map.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/papilo-external/lusol" TYPE FILE FILES "/mnt/d/aMain/4-pre/pre/papilo/external/lusol/clusol.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/papilo" TYPE FILE FILES "/mnt/d/aMain/4-pre/pre/build/papilo/CMakeFiles/papilo-config.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/papilo" TYPE FILE FILES "/mnt/d/aMain/4-pre/pre/papilo/cmake/Modules/FindQuadmath.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/papilo" TYPE FILE FILES "/mnt/d/aMain/4-pre/pre/build/papilo/CMakeFiles/papilo-config.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/papilo" TYPE FILE FILES "/mnt/d/aMain/4-pre/pre/papilo/cmake/Modules/FindTBB.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/papilo/papilo-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/papilo/papilo-targets.cmake"
         "/mnt/d/aMain/4-pre/pre/build/papilo/CMakeFiles/Export/lib/cmake/papilo/papilo-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/papilo/papilo-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/papilo/papilo-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/papilo" TYPE FILE FILES "/mnt/d/aMain/4-pre/pre/build/papilo/CMakeFiles/Export/lib/cmake/papilo/papilo-targets.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/mnt/d/aMain/4-pre/pre/build/papilo/binaries/cmake_install.cmake")
  include("/mnt/d/aMain/4-pre/pre/build/papilo/test/cmake_install.cmake")

endif()

