#include "../../enola/graph/graph.hpp"

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
