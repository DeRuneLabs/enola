add_executable(tensor_example tensor_usage.cc)
add_executable(sigmoid_example sigmoid_usage.cc)
add_executable(relu_usage relu_usage.cc)
add_executable(relu_derivative_usage relu_derivative_usage.cc)
add_executable(binary_step_example binary_step_usage.cc)
add_executable(softplus_example softplus_usage.cc)
add_executable(squareplus_example squareplus_usage.cc)
add_executable(swish_example swish_usage.cc)
add_executable(elu_example elu_usage.cc)
add_executable(neural_network_example neural_network/simple_neural_network.cc)

target_include_directories(tensor_example
                           PRIVATE ${PROJECT_SOURCE_DIR}/enola/tensor)
target_include_directories(sigmoid_example
                           PRIVATE ${PROJECT_SOURCE_DIR}/enola/function)
target_include_directories(
  relu_usage PRIVATE ${PROJECT_SOURCE_DIR}/enola/function/activation)

target_include_directories(
  relu_derivative_usage PRIVATE ${PROJECT_SOURCE_DIR}/enola/function/activation)

target_include_directories(
  binary_step_example PRIVATE ${PROJECT_SOURCE_DIR}/enola/function/activation)

target_include_directories(
  softplus_example PRIVATE ${PROJECT_SOURCE_DIR}/enola/function/activation)

target_include_directories(
  softplus_example PRIVATE ${PROJECT_SOURCE_DIR}/enola/function/activation)

target_include_directories(
  swish_example PRIVATE ${PROJECT_SOURCE_DIR}/enola/function/activation)

target_include_directories(
  elu_example PRIVATE ${PROJECT_SOURCE_DIR}/enola/function/activation)

target_include_directories(
  neural_network_example
  PRIVATE ${PROJECT_SOURCE_DIR}/enola/function/activation)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                           "Clang")
  target_compile_options(tensor_example PRIVATE -Wno-non-template-friend
                                                -Wno-unused-result)
endif()
