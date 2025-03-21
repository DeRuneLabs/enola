add_executable(
  run_tests
  main_test.cc
  graph_test.cc
  bintree_test.cc
  avl_tree_test.cc
  dsjoint_set_test.cc
  tensor_test.cc
  iterator_link_list_test.cc
  iterator_list_iterator_test.cc
  list_linked_list_test.cc)
target_link_libraries(run_tests GTest::GTest GTest::Main)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                           "Clang")
  target_compile_options(run_tests PRIVATE -Wno-non-template-friend)
endif()

enable_testing()
