cmake_minimum_required (VERSION 3.0)
project (span_ndTest CXX)

#flags/defines
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wpedantic -Og")

#packages
find_package (GTest REQUIRED)
find_package (Threads REQUIRED)

#includes
include_directories (${GTEST_INCLUDE_DIRS})

#executable
add_executable (span_ndTest test.cpp constrTest.cpp)
target_link_libraries (span_ndTest gtest gtest_main pthread)

add_test(span_ndTest span_ndTest)
