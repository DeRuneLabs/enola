add_executable(
  run_tests
  function_sigmoid_test.cc
  function_activation_relu_test.cc
  function_activation_binary_step_test.cc
  function_activation_softplus_test.cc
  function_activation_squareplus.cc
  function_activation_swish.cc
  function_activation_elu_test.cc
  ops_deep_copy_test.cc
  math_abs_test.cc
  math_ceil_test.cc
  math_exp_test.cc
  nn_test.cc
  tensor_tensor_storage_test.cc
  tensor_view_test.cc
  tensor_ops_test.cc
  score_mae_test.cc
  score_msle_test.cc)

target_link_libraries(run_tests PRIVATE GTest::GTest GTest::Main)

target_include_directories(
  run_tests
  PRIVATE ${PROJECT_SOURCE_DIR}/enola ${PROJECT_SOURCE_DIR}/enola/tensor
          ${PROJECT_SOURCE_DIR}/enola/function
          ${PROJECT_SOURCE_DIR}/enola/function/activation)

find_package(OpenCL REQUIRED)

if(OpenCL_FOUND)
  message(
    STATUS "openCL found: including OpenCL headers and linking OpenCL library")
  target_include_directories(run_tests PRIVATE ${OpenCL_INCLUDE_DIRS})
  target_link_libraries(run_tests PRIVATE ${OpenCL_LIBRARIES})
else()
  message(
    FATAL_ERROR "opencl not found: please install OpenCL development libraries")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                           "Clang")
  target_compile_options(run_tests PRIVATE -Wno-non-template-friend
                                           -Wno-unused-result)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                           "Clang")
  target_compile_options(run_tests PRIVATE -Wno-non-template-friend
                                           -Wno-unused-result)
endif()

enable_testing()
add_test(NAME run_tests COMMAND run_tests)
