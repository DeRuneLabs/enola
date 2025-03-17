#include "../enola/graph/graph.hpp"
#include <iostream>

int main() {
  Graph<int> graph("undirected");

  graph.add_edge(0, 1, 5);
  graph.add_edge(0, 2, 3);
  graph.add_edge(1, 2, 2);
  graph.add_edge(1, 3, 4);
  graph.add_edge(2, 3, 7);

  std::cout << "DFS traversal (from 0): ";
  std::vector<int> dfs_result = graph.dfs(0);
  for (int node : dfs_result) {
    std::cout << node << " ";
  }
  std::cout << std::endl;

  return 0;
}
