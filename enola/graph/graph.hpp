#ifndef GRAPH_GRAPH_HPP_
#define GRAPH_GRAPH_HPP_

#include <climits>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

template <typename T>
class graph {
 public:
  graph(std::string __type) {
    try {
      if (__type == "directed" || __type == "undirected") {
        this->__type = __type;
      } else {
        throw std::invalid_argument("cannot recognized the type of graph");
      }
    } catch (std::invalid_argument &error) {
      std::cerr << error.what() << "\n";
      return;
    }
  }

  ~graph() {}

  void add_edge(T u, T v, int64_t w) {
    if (__type == "undirected") {
      adj[u].push_back(v);
      adj[v].push_back(u);
    } else {
      adj[u].push_back(v);
    }
  }

  std::vector<T> dfs(T start) {
    std::stack<T>               s;
    std::vector<T>              path;
    std::unordered_map<T, bool> visited;

    s.push(start);

    visited[start] = true;
    while (!s.empty()) {
      T current = s.top();
      path.push_back(current);
      s.pop();

      for (T &x : adj[current]) {
        if (visited.find(x) == visited.end()) {
          s.push(x);
          visited[x] = true;
        }
      }
    }

    return path;
  }

  std::vector<T> bfs(T start) {
    std::queue<T>               q;
    std::vector<T>              path;
    std::unordered_map<T, bool> visited;

    q.push(start);

    visited[start] = true;
    while (!q.empty()) {
      int64_t size = q.size();
      for (int64_t i = 0; i < size; i++) {
        T current = q.front();
        path.push_back(current);
        q.pop();

        for (T &x : adj[current]) {
          if (visited.find(x) == visited.end()) {
            q.push(x);
            visited[x] = true;
          }
        }
      }
    }
    return path;
  }

 private:
  std::unordered_map<T, T> adj;
  std::string              __type;
};

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
template <typename T>
class weight_graph {
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
  weight_graph(std::string __type) {
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
  ~weight_graph() { adj.clear(); }

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
    std::stack<T>               s;        // stack simulate recursion
    std::vector<T>              path;     // store traversal oreder
    std::unordered_map<T, bool> visited;  // tracking visited nodes

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
    std::queue<T>               q;     // queue to process nodes level by level
    std::vector<T>              path;  // store the traversal order
    std::unordered_map<T, bool> visited;  // track visited order

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

  /**
   * @brief find the shortest path between two nodes in weight graph using
   * djikstra algorithm
   *
   * this function implements djikstra algorithm to compute the shortest path
   * from a start node to an end node in a graph represented by an adjacency
   * list. The graph is assumed to have non-negative edge weights
   *
   * @tparam T type of the nodes in the graphs
   * @param start the starting node for the shorterts path search
   * @param end the target node for the shorthest path search
   * @return int64_t shortest path distance from the start node to the end node.
   * if not path exist the function return -1
   */
  int64_t shortest_path(T start, T end) {
    // initialize map to store distance from the start node to each node
    // initially, all distance are set to infinity (INT_MAX), execpt for the
    // start node
    std::unordered_map<T, int64_t> dist;
    for (auto &x : __elements) {  // iterate all node in the graph
      dist[x] = INT_MAX;          // set initial distance to the `infinity`
    }
    // priority queue to processing node in order of their current shortest
    // distance queue store pairs of (distance and node), sorted by smallest
    // distance first
    std::priority_queue<std::pair<int64_t, T>,
                        std::vector<std::pair<int64_t, T>>,
                        std::greater<std::pair<int64_t, T>>>
        pq;
    // push the start node into the priority queue with distance of 0
    pq.push_back(std::make_pair(0, start));
    dist[start] = 0;  // distance to the start node is 0

    // process node until the priority empty
    while (!pq.empty()) {
      // extract node with the smallest current distance from the priority queue
      T currentNode = pq.top().second;  // node will process
      T currentDist = pq.top().first;  // current shortest distance to this node
      pq.pop();

      // iterating over the outgoing edeg of the current node
      for (std::pair<T, int64_t> &edge : adj[currentNode]) {
        if (currentDist + edge.second < dist[edge.first]) {
          dist[edge.first] = currentDist + edge.second;
          pq.push(std::make_tuple(dist[edge.first], edge.first));
        }
      }
    }
    // return the shorthest path distance the end node, or -1 if path no exists
    return (dist[end] != INT_MAX) ? dist[end] : -1;
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
  /**
   * @brief representing the set of all element nodes in the graph
   */
  std::unordered_set<T> __elements;
};

#endif  // ! GRAPH_GRAPH_HPP_
