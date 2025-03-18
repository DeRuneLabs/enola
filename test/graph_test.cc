#include "../enola/graph/graph.hpp"
#include <gtest/gtest.h>

TEST(GraphTest, ConstructorGraph) {
  EXPECT_NO_THROW(graph<int> graph1("directed"));
  EXPECT_NO_THROW(graph<int> graph2("undirected"));
}

TEST(GraphTest, ConstructorWeightGraph) {
  EXPECT_NO_THROW(weight_graph<int> directed("directed"));
  EXPECT_NO_THROW(weight_graph<int> undirected("undirected"));
}

TEST(GraphTest, AddEdgeDirected) {
  weight_graph<int> graph("directed");

  graph.add_edge(1, 2, 10);
  graph.add_edge(2, 3, 30);
  graph.add_edge(3, 4, 40);

  std::vector<int> dfs_result = graph.dfs(1);
  std::vector<int> expected = {1, 2, 3, 4};
  EXPECT_EQ(dfs_result, expected);
}

TEST(GraphTest, DFSTraversalDirected) {
  weight_graph<int> graph("directed");

  graph.add_edge(1, 2, 10);
  graph.add_edge(2, 3, 20);
  graph.add_edge(3, 4, 30);

  std::vector<int> result = graph.dfs(1);
  std::vector<int> expected = {1, 2, 3, 4};
  EXPECT_EQ(result, expected);
}

TEST(GraphTest, BFSTraversalDirected) {
  weight_graph<int> graph("directed");

  graph.add_edge(1, 2, 10);
  graph.add_edge(2, 3, 20);
  graph.add_edge(3, 4, 30);

  std::vector<int> result = graph.bfs(1);
  std::vector<int> expected = {1, 2, 3, 4};
  EXPECT_EQ(result, expected);
}
