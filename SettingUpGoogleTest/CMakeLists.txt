cmake_minimum_required(VERSION 3.8)
project(SettingUpGoogleTest)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)



set(SOURCE_FILES main.cpp tests/ClassName.hpp tests/test.cpp)
add_executable(SettingUpGoogleTest ${SOURCE_FILES} tests/ClassName.hpp tests/test.cpp)
target_link_libraries(SettingUpGoogleTest gtest gtest_main)