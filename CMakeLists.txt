# Sets the project name
project(CxxDBC)

# Using CMake 2.8
cmake_minimum_required(VERSION 2.8)

# Set flags for building that are common to all build modes
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic -std=c++1y -pthread")

# Define the flags for building C++ in release mode
set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")

# Define the flags for building C++ in release mode
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -gdwarf-4")

# Make sure the comip

# Enumerate the source files
add_library(cxxdbc
  ./src/driver_manager.cpp
  )

# Enumerate the test source files
set(cxxdbc_test_SOURCES
  ./test/unit/1.0/driver_manager.t.cpp
  ./test/unit/1.0/blob.t.cpp
  ./test/unit/1.0/connection.t.cpp
  ./test/unit/1.0/exception.t.cpp
  ./test/unit/1.0/result_set.t.cpp
  ./test/unit/1.0/result_set_meta_data.t.cpp
  ./test/unit/1.0/statement.t.cpp
  )

# Adds CxxDBC directories that contain headers to the project
include_directories(./include)

# Create a binary that executes all the CxxDBC unit tests
add_executable(cxxdbc_test ${cxxdbc_test_SOURCES})

# Set up gtest
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(cxxdbc_test cxxdbc ${GTEST_BOTH_LIBRARIES} sqlite3)

# Wires up the tests to `make test`
add_test(NAME AllCxxDBCTests COMMAND cxxdbc_test)
