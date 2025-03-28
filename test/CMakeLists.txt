add_executable(
  run_tests
  tensor_tensor_storage_test.cc
  function_sigmoid_test.cc
  function_activation_relu_test.cc
  function_activation_binary_step_test.cc
  function_activation_softplus_test.cc
  function_activation_squareplus.cc
  function_activation_swish.cc
  function_activation_elu_test.cc
  nn_test.cc)

target_link_libraries(run_tests PRIVATE GTest::GTest GTest::Main)

target_include_directories(
  run_tests
  PRIVATE ${PROJECT_SOURCE_DIR}/enola ${PROJECT_SOURCE_DIR}/enola/tensor
          ${PROJECT_SOURCE_DIR}/enola/function
          ${PROJECT_SOURCE_DIR}/enola/function/activation)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                           "Clang")
  target_compile_options(run_tests PRIVATE -Wno-non-template-friend)
endif()

enable_testing()
add_test(NAME run_tests COMMAND run_tests)
