cmake_minimum_required(VERSION 3.26)
project(compl)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(compl
        solution.cpp
        solution.h)
