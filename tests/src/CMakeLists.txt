cmake_minimum_required(VERSION 3.20)
project(compl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})


include_directories(../../src/common)

add_executable(compl
        tests.cpp
        ../../src/common/solution.h)
target_link_libraries(compl ${GTEST_LIBRARIES} pthread)
