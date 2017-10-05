cmake_minimum_required(VERSION 3.8)
project(direct_access_fixed_length)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp test_one.cpp test_two.cpp DataFile.cpp DataFile.h)
add_executable(direct_access_fixed_length ${SOURCE_FILES})