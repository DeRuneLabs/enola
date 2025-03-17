add_executable(run_tests main_test.cc graph_test.cc bintree_test.cc)
target_link_libraries(run_tests GTest::GTest GTest::Main)

enable_testing()
add_test(NAME WeightedGraphTests COMMAND run_tests)
add_test(NAME BintreeTests COMMAND run_tests)
