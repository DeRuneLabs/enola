add_executable(run_tests main_test.cc graph_test.cc bintree_test.cc
                         avl_tree_test.cc dsjoint_set_test.cc)
target_link_libraries(run_tests GTest::GTest GTest::Main)

enable_testing()
