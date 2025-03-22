add_executable(tensor_example tensor_usage.cc)
add_executable(sigmoid_example sigmoid_usage.cc)
add_executable(relu_usage relu_usage.cc)

target_include_directories(tensor_example
                           PRIVATE ${PROJECT_SOURCE_DIR}/enola/tensor)
target_include_directories(sigmoid_example
                           PRIVATE ${PROJECT_SOURCE_DIR}/enola/function)
target_include_directories(
  relu_usage PRIVATE ${PROJECT_SOURCE_DIR}/enola/function/activation)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                           "Clang")
  target_compile_options(tensor_example PRIVATE -Wno-non-template-friend
                                                -Wno-unused-result)
endif()
