cmake_minimum_required(VERSION 3.8)
project(basic_tests)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(basic_tests ${SOURCE_FILES})