cmake_minimum_required(VERSION 3.10)
project(enola LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_library(enola_headers INTERFACE)
target_include_directories(
  enola_headers
  INTERFACE ${PROJECT_SOURCE_DIR}/enola/tensor
            ${PROJECT_SOURCE_DIR}/enola/function
            ${PROJECT_SOURCE_DIR}/enola/score ${PROJECT_SOURCE_DIR}/enola/ops)

find_package(OpenCL QUIET)
if(OpenCL_FOUND)
  message(STATUS "opencl found: enable GPU support")
  add_definitions(-DGPU_SUPPORT_AVAILABLE)
else()
  message(STATUS "opencl not found: GPU support will disable")
endif()

find_package(GTest REQUIRED)
add_library(gtest_headers INTERFACE)
target_include_directories(gtest_headers INTERFACE {GTEST_INCLUDE_DIRS})

# cmake -S . -B build -DBUILD_EXAMPLES=ON
option(BUILD_EXAMPLE "build example program" OFF)

if(BUILD_EXAMPLE)
  add_subdirectory(example)
endif()

option(TEST_ENOLA "test enola library" ON)
if(TEST_ENOLA)
  add_subdirectory(test)
endif()
