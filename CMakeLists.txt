cmake_minimum_required(VERSION 3.10)
project(enola LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(enola_headers INTERFACE)
target_include_directories(enola_headers
                           INTERFACE ${PROJECT_SOURCE_DIR}/enola/tensor)

find_package(GTest REQUIRED)
add_library(gtest_headers INTERFACE)
target_include_directories(gtest_headers INTERFACE {GTEST_INCLUDE_DIRS})

add_subdirectory(example)
add_subdirectory(test)
