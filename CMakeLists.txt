cmake_minimum_required(VERSION 3.10)
project(enola)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(enola/graph)
include_directories(enola/tree)
include_directories(enola/dsjoint_set)
include_directories(enola/matrix)
include_directories(enola/plot/iterator)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory(example)
add_subdirectory(test)
