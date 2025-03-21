#include "../enola/graph/graph.hpp"

#include <gtest/gtest.h>

#include <algorithm>

TEST(GraphTest, ConstructorGraph) {
  EXPECT_NO_THROW(graph<int> graph1("directed"));
  EXPECT_NO_THROW(graph<int> graph2("undirected"));
}

TEST(GraphTest, AddEdgeDirected) {
  graph<int> graph_data("directed");

  graph_data.add_edge(1, 2, 10);
  graph_data.add_edge(2, 3, 30);
  graph_data.add_edge(3, 4, 10);

  std::vector<int> dfs_result = graph_data.dfs(1);
  std::vector<int> expected   = {1, 2, 3, 4};
  EXPECT_EQ(dfs_result, expected);
}

TEST(GraphTest, DFSTraversalDirected) {
  graph<int> graph_data("directed");

  graph_data.add_edge(1, 2, 10);
  graph_data.add_edge(2, 3, 20);
  graph_data.add_edge(3, 4, 30);

  std::vector<int> result   = graph_data.dfs(1);
  std::vector<int> expected = {1, 2, 3, 4};
  EXPECT_EQ(result, expected);
}

TEST(GraphTest, AddEdgeUndirected) {
  graph<int> graph_data("undirected");

  graph_data.add_edge(1, 2, 10);
  graph_data.add_edge(2, 3, 20);
  graph_data.add_edge(3, 4, 30);

  std::vector<int> result   = graph_data.dfs(1);
  std::vector<int> expected = {1, 2, 3, 4};
  EXPECT_EQ(result.size(), expected.size());
  EXPECT_TRUE(
      std::is_permutation(result.begin(), result.end(), expected.begin()));
}

TEST(GraphTest, BFSTraversalUndirected) {
  graph<int> graph_data("undirected");

  graph_data.add_edge(1, 2, 10);
  graph_data.add_edge(2, 3, 20);
  graph_data.add_edge(3, 4, 30);

  std::vector<int> result   = graph_data.bfs(1);
  std::vector<int> expected = {1, 2, 3, 4};
  EXPECT_EQ(result.size(), expected.size());
  EXPECT_TRUE(
      std::is_permutation(result.begin(), result.end(), expected.begin()));
}

TEST(WeightGraphTest, ConstructorValidType) {
  EXPECT_NO_THROW(weight_graph<int> graph_1("directed"));
  EXPECT_NO_THROW(weight_graph<int> graph_2("undirected"));
}

TEST(WeightGraphTest, AddEdgeDirected) {
  weight_graph<int> graph_data("directed");

  graph_data.add_edge(1, 2, 10);
  graph_data.add_edge(2, 3, 20);
  graph_data.add_edge(3, 4, 30);

  EXPECT_EQ(graph_data.dfs(1), std::vector<int>({1, 2, 3, 4}));
}

TEST(WeightGraphTest, AddEdgeUndirected) {
  weight_graph<int> graph_data("undirected");

  graph_data.add_edge(1, 2, 10);
  graph_data.add_edge(2, 3, 20);
  graph_data.add_edge(3, 4, 30);

  std::vector<int> result   = graph_data.dfs(1);
  std::vector<int> expected = {1, 2, 3, 4};
  EXPECT_TRUE(
      std::is_permutation(result.begin(), result.end(), expected.begin()));
}

TEST(WeightGraphTest, DFSTraversalDirected) {
  weight_graph<int> graph_data("directed");

  graph_data.add_edge(1, 2, 10);
  graph_data.add_edge(2, 3, 20);
  graph_data.add_edge(3, 4, 30);

  std::vector<int> result   = graph_data.dfs(1);
  std::vector<int> expected = {1, 2, 3, 4};
  EXPECT_EQ(result, expected);
}
