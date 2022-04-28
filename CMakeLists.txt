cmake_minimum_required(VERSION 3.10)
project(pre)

set(CMAKE_CXX_STANDARD 17)
get_property(languages GLOBAL PROPERTY ENABLED_LANGUAGES)
message(STATUS "languages: ${languages}")

if (NOT CMAKE_BUILD_TYPE)
    message(WARNING "Please use -DCMAKE_BUILD_TYPE=[build_type] where [build_type] is one of: Debug, Release, RelWithDebInfo and MinSizeRel")
endif()


include_directories(
    src
    papilo/src
    papilo/external
)

# Boost
SET (BOOST_ROOT "/usr/local/Cellar/boost/1.75.0_2")
SET (BOOST_INCLUDEDIR "/usr/local/Cellar/boost/include/1.75.0_2")
SET (BOOST_LIBRARYDIR "/usr/local/Cellar/boost/lib/1.75.0_2")

set (Boost_NO_BOOST_CMAKE ON)
find_package(Boost ${BOOST_MIN_VERSION} REQUIRED serialization program_options iostreams system filesystem)
if (NOT Boost_FOUND)
  message(FATAL_ERROR "Fatal error: Boost (version >= 1.55) required.")
else()
  message(STATUS "Setting up BOOST")
  message(STATUS " Includes - ${Boost_INCLUDE_DIRS}")
  message(STATUS " Library  - ${Boost_LIBRARY_DIRS}")
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
endif (NOT Boost_FOUND)

# Papilo
add_subdirectory(papilo)
set(PAPILO_DIR ${CMAKE_BINARY_DIR})

find_package(PAPILO CONFIG)


# file(GLOB SOURCES "src/*.cpp")
set(source_files
  src/utils.cpp
  src/Constr.cpp
  src/parsing.cpp
  src/MIP.cpp
  src/SAT.cpp
  src/runRoundingSat.cpp
  src/main.cpp
  ${PROJECT_SOURCE_DIR}/src/typedef.hpp
  ${PROJECT_SOURCE_DIR}/src/runRoundingSat.hpp
  ${PROJECT_SOURCE_DIR}/src/auxiliary.hpp
  ${PROJECT_SOURCE_DIR}/src/Constr.hpp
  ${PROJECT_SOURCE_DIR}/src/utils.hpp
  ${PROJECT_SOURCE_DIR}/src/parsing.hpp
  ${PROJECT_SOURCE_DIR}/src/MIP.hpp
  ${PROJECT_SOURCE_DIR}/src/SAT.hpp
  )

add_executable(pre ${source_files})
# target_include_directories(pre PRIVATE ${PROJECT_SOURCE_DIR}/src/ )
target_link_libraries(pre ${PAPILO_IMPORTED_TARGETS} ${Boost_LIBRARIES})
# target_link_libraries(PresolveOpb PRIVATE Boost::serialization)

FIND_PROGRAM(CLANG_FORMAT "clang-format")
IF(CLANG_FORMAT)
    add_custom_target(
        format
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMAND ${CLANG_FORMAT}
        -style=file
        -i
        ${all_files}
    )
endif()