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

target_link_libraries(run_tests PRIVATE GTest::GTest GTest::Main)

target_include_directories(
  run_tests
  PRIVATE ${PROJECT_SOURCE_DIR}/enola/graph
          ${PROJECT_SOURCE_DIR}/enola/tree
          ${PROJECT_SOURCE_DIR}/enola/dsjoint_set
          ${PROJECT_SOURCE_DIR}/enola/matrix
          ${PROJECT_SOURCE_DIR}/enola/plot/iterator
          ${PROJECT_SOURCE_DIR}/enola/list)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                           "Clang")
  target_compile_options(run_tests PRIVATE -Wno-non-template-friend)
endif()

enable_testing()
add_test(NAME run_tests COMMAND run_tests)
