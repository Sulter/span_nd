cmake_minimum_required(VERSION 3.0)
project(span_nd LANGUAGES CXX)

add_library(span_nd INTERFACE)
target_sources(span_nd INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/span_nd.hpp)
target_include_directories(span_nd INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(span_nd INTERFACE cxx_std_14)

option(ENABLE_TESTING "Build and enable testing" ON)
if(ENABLE_TESTING)
  enable_testing()
endif(ENABLE_TESTING)

if(ENABLE_TESTING)
  add_subdirectory(test)
endif(ENABLE_TESTING)
