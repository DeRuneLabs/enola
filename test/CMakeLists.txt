add_executable(run_tests tensor_tensor_storage_test.cc)

target_link_libraries(run_tests PRIVATE GTest::GTest GTest::Main)

target_include_directories(run_tests PRIVATE ${PROJECT_SOURCE_DIR}/enola/tensor)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                           "Clang")
  target_compile_options(run_tests PRIVATE -Wno-non-template-friend)
endif()

enable_testing()
add_test(NAME run_tests COMMAND run_tests)
