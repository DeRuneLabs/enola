#include "../enola/graph/graph.hpp"
#include <gtest/gtest.h>

TEST(GraphTest, Constructor) {
  Graph<int> graph("directed");
  EXPECT_NO_THROW(Graph<int>("directed"));
  EXPECT_NO_THROW(Graph<int>("undirected"));
}

TEST(GraphTest, AddEdge) {
  Graph<int> graph("undirected");
  graph.add_edge(1, 2, 10);
  graph.add_edge(2, 3, 20);

  EXPECT_EQ(graph.dfs(1).size(), 3);
}

TEST(GraphTest, DFSTraversal) {
  Graph<int> graph("undirected");
  graph.add_edge(1, 2, 10);
  graph.add_edge(2, 3, 20);
  graph.add_edge(3, 4, 30);

  std::vector<int> expected_dfs = {1, 2, 3, 4};
  std::vector<int> result_dfs = graph.dfs(1);

  EXPECT_EQ(result_dfs, expected_dfs);
}
