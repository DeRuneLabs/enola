add_executable(graph_example graph/graph.cc)
add_executable(bintree_example tree/bintree.cc)
add_executable(avl_tree_example tree/avl_tree.cc)
add_executable(dsjoint_example dsjoint_set/dsjoint_set.cc)
add_executable(tensor_example matrix/tensor.cc)
add_executable(linked_list_example list/linked_list.cc)

target_include_directories(graph_example
                           PRIVATE ${PROJECT_SOURCE_DIR}/enola/graph)
target_include_directories(bintree_example
                           PRIVATE ${PROJECT_SOURCE_DIR}/enola/tree)
target_include_directories(avl_tree_example
                           PRIVATE ${PROJECT_SOURCE_DIR}/enola/tree)
target_include_directories(dsjoint_example
                           PRIVATE ${PROJECT_SOURCE_DIR}/enola/dsjoint_set)
target_include_directories(tensor_example
                           PRIVATE ${PROJECT_SOURCE_DIR}/enola/matrix)
target_include_directories(linked_list_example
                           PRIVATE ${PROJECT_SOURCE_DIR}/enola/list)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL
                                           "Clang")
  target_compile_options(linked_list_example PRIVATE -Wno-non-template-friend
                                                     -Wno-unused-result)
endif()
