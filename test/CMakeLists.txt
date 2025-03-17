add_executable(run_tests main_test.cpp graph_test.cpp)
target_link_libraries(run_tests GTest::GTest GTest::Main)

enable_testing()
add_test(NAME GraphTests COMMAND run_tests)
