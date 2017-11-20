cmake_minimum_required(VERSION 3.8)
project(snake)

link_directories(${OPENGL_gl_LIBRARY})

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Point.hpp Apple.hpp Snake.hpp)
add_executable(snake ${SOURCE_FILES} Point.hpp Apple.hpp Snake.hpp)