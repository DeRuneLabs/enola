#ifndef GRAPH_GRAPH_HPP_
#define GRAPH_GRAPH_HPP_

#include <cstdint>
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

/**
 * @file Graph.hpp
 * @brief template-base graph implementation supporting and undirected graphs
 *
 * This class provide functionally to representing graph using adjacency list
 * - adding edges (weighted) between nodes
 * - perform depth-first search traversal
 * - performing breadth-first-search traversal
 *
 * the graph can be either directed or undirecte, specified during
 * initialization
 * @tparam T the type of the nodes in the graph
 */
template <typename T> class Graph {
public:
  /**
   * @brief Constructor to initialize the graph with a specific type
   *
   * the graph type can be either "directed" or "directed", if invalid type
   * an execption is thrown and error messagfe is printed
   *
   * @param __type string specifying the type of the graph ("directed" or
   * "undirected")
   */
  Graph(std::string __type) {
    try {
      if (__type == "directed" || __type == "undirected") {
        this->__type = __type;
      } else {
        throw std::invalid_argument("cannot recognize type of the graph");
      }
    } catch (std::invalid_argument &error) {
      std::cerr << error.what() << '\n';
      return;
    }
  }

  /**
   * @brief Desctructor to clean up resources
   *
   * clears the adjacency list to free memory
   */
  ~Graph() { adj.clear(); }

  /**
   * @brief add an edge between to nodes with a given weight
   *
   * if the graph is undirected, the edge is added in both directions, for
   * directed graphs the edge is added only from node `u` to node `v`
   *
   * @param u the source node
   * @param v the destination node
   * @param w the weight the edge between u and v
   */
  void add_edge(T u, T v, int64_t w) {
    if (__type == "undirected") {
      adj[u].push_back(std::make_pair(v, w));
      adj[v].push_back(std::make_pair(u, w));
    } else if (__type == "directed") {
      adj[u].push_back(std::make_pair(v, w));
    }
  }

  /**
   * @brief perform depth first search (DFS) traversal starting from given node
   *
   * DFS explore as far as possibel along each branch before backtraking. the
   * traversal order is stored in a vector and returned
   *
   * @param start the starting node for the DFS traversal
   * @return vector containing the node visited in DFS order
   */
  std::vector<T> dfs(T start) {
    std::stack<T> s;                     // stack simulate recursion
    std::vector<T> path;                 // store traversal oreder
    std::unordered_map<T, bool> visited; // tracking visited nodes

    s.push(start);
    visited[start] = true;

    while (!s.empty()) {
      T current = s.top();
      path.push_back(current);

      s.pop();
      for (std::pair<T, int64_t> &x : adj[current]) {
        if (visited.find(x.first) == visited.end()) {
          s.push(x.first);
          visited[x.first] = true;
        }
      }
    }
    return path;
  }

  /**
   * @brief perform a Breadth-First Search (BFS) traversal starting from a given
   * node
   *
   * bfs explore all neighbors at the present depth level before moving on to
   * nodes at the next depth level. the traversal order is stored in a vector
   * and returned
   *
   * @param start starting node for the BFS traversal
   * @return vector containing node visited in BFS order
   */
  std::vector<T> bfs(T start) {
    std::queue<T> q;     // queue to process nodes level by level
    std::vector<T> path; // store the traversal order
    std::unordered_map<T, bool> visited; // track visited order

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
      int64_t size = q.size();

      for (int64_t i = 0; i < size; i++) {
        T current = q.front();
        path.push_back(current);
        q.pop();

        for (std::pair<T, int64_t> &x : adj[current]) {
          if (visited.find(x.first) == visited.end()) {
            q.push(x.first);
            visited[x.first] = true;
          }
        }
      }
    }
    return path;
  }

private:
  /**
   * @brief adjacency list representation of the graph
   *
   * each key in the map represents a node, and the corresponding value is a
   * vector of pairs
   */
  std::unordered_map<T, std::vector<std::pair<T, int64_t>>> adj;
  /**
   * @brief type of the graph ("directed" or "undirected")
   */
  std::string __type;
};

#endif // ! GRAPH_GRAPH_HPP_
