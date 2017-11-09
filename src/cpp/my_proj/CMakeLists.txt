cmake_minimum_required(VERSION 3.8)
project(my_proj)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Base.cpp Base.h Derived.cpp Derived.h)
add_executable(my_proj ${SOURCE_FILES})