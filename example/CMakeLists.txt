add_executable(graph_example graph/graph.cc)
add_executable(bintree_example tree/bintree.cc)
add_executable(avl_tree_example tree/avl_tree.cc)
add_executable(dsjoint_example dsjoint_set/dsjoint_set.cc)
add_executable(tensor_example matrix/tensor.cc)
add_executable(linked_list_example list/linked_list.cc)

target_compile_options(linked_list_example PRIVATE -Wno-non-template-friend -Wno-unused-result)
