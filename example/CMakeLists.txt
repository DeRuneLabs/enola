add_executable(tensor_example tensor_usage.cc)

target_include_directories(tensor_example
                           PRIVATE ${PROJECT_SOURCE_DIR}/enola/tensor)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                           "Clang")
  target_compile_options(tensor_example PRIVATE -Wno-non-template-friend
                                                     -Wno-unused-result)
endif()
