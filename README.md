# enola
library for perform some complex data structure algorithms, currently this library support
- graph
- dsjoint set
- tree
    - avl_tree
    - binary tree

## example use

- graph
```cpp
#include <enola/graph/graph.hpp>
#include <iostream>

int main() {
    weight_graph<int> directed_graph("directed");

  std::cout << "test to add the directed graph" << std::endl;
  directed_graph.add_edge(1, 2, 10);
  directed_graph.add_edge(2, 3, 20);
  directed_graph.add_edge(3, 4, 30);
  directed_graph.add_edge(1, 3, 50);

  std::cout << "DFS traversal (directed graph): ";
  std::vector<int> dfs_result = directed_graph.dfs(1);
  for (int node : dfs_result) {
    std::cout << node << " ";
  }
  std::cout << std::endl;

  weight_graph<int> undirectedGraph("undirected");
  std::cout << "add edges to the undirected graph" << std::endl;
  undirectedGraph.add_edge(1, 2, 10);
  undirectedGraph.add_edge(2, 3, 20);
  undirectedGraph.add_edge(3, 4, 30);
  undirectedGraph.add_edge(1, 3, 50);
  std::cout << "DFS traversal (undirected graph): ";
  dfs_result = undirectedGraph.dfs(1);
  for (int node : dfs_result) {
    std::cout << node << " ";
  }
  std::cout << std::endl;

  return 0;
}
```

- tensor
```cpp
#include <enola/matrix/tensor.hpp>
#include <iostream>

int main() {
  tensor t(2, 3, 4);

  t(0, 0, 0) = 42; 
  t(1, 2, 3) = 99;

  std::cout << "element (0, 0, 0): " << t(0, 0, 0) << std::endl;
  std::cout << "element (1, 2, 3): " << t(1, 2, 3) << std::endl;

  auto [dim1, dim2, dim3] = t.get_dimension();
  std::cout << "dimensions: " << dim1 << " x " << dim2 << " x " << dim3 << std::endl;

  return 0;
}
```
