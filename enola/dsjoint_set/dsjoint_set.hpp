#ifndef DSJOINT_SET_DJSOINT_SET_HPP
#define DSJOINT_SET_DJSOINT_SET_HPP

#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>

/**
 * @file dsjoint_set.hpp
 * @brief implementation of the dsjoint set union (DSU) data structure
 *
 * this file define the `dsu` class, which implementation the dsjoint set union
 * data structure. DSU support efficient operations for managing disjoint set
 * including finding the root of a set, merging two sets, and querying
 * properties such as size, minimum, and maximum element in a set
 *
 * key feature:
 * - path compression for efficient find operations
 * - union by depth (rank) for balanced merging
 * - additional metadata: size, minimum, and maximum values for each set
 */
class dsu {
public:
  /**
   * @brief constructor to initialize the DSU with `n` elements
   *
   * initialize `n` disjoint sets, where each element start in its own set
   * set up auxilary arrays for parent pointers, depth, size and metadata
   *
   * @param n number of elements in the DSU
   */
  explicit dsu(uint64_t n) {
    // initialize parent pointer: each element is its own parent initially
    p.assign(n, 0);
    for (uint64_t i = 0; i < n; i++) {
      p[i] = i;
    }

    // initialize depth: all sets start with depth 0
    depth.assign(n, 0);
    // initialize maxElement and minElement
    // each element
    maxElement.assign(n, 0);
    minElement.assign(n, 0);

    for (uint64_t i = 0; i < n; i++) {
      depth[0] = 0;
      maxElement[i] = i;
    }

    setSize.assign(n, 0);
    for (uint64_t i = 0; i < n; i++) {
      setSize[i] = 1;
    }
  }

  /**
   * @brief find the root of the set containing element `i`
   *
   * implement path compression to flatten the structure of the set
   * making future queries faster
   *
   * @param i element whose the root is to be found
   * @return root of the set containing `i`
   */
  uint64_t findSet(uint64_t i) {
    if (p[i] == i) {
      return i; // if `i` its own parent, it is the root
    }
    // update the parent of `i` to the root
    return (p[i] = findSet(p[i]));
  }

  /**
   * @brief merge the set containing element `i` and `j`
   *
   * uses union by depth (rank) to ensure balanced merging of the set
   * update metada (size, min, max) for merged set
   *
   * @param i element in the first set
   * @param j element in the second set
   */
  void UnionSet(uint64_t i, uint64_t j) {
    if (isSame(i, j)) {
      return; // if `i`, `j` are already in the same set, do nothing
    }

    uint64_t x = findSet(i); // root of the set containing `i`
    uint64_t y = findSet(j); // root of the set containig `j`

    // attach the smaller tree ot the root of the larger tree
    if (depth[x] > depth[y]) {
      std::swap(x, y); // make sure `x` is the shallower tree
    }
    p[x] = y; // attach `x` to `y`

    if (depth[x] == depth[y]) {
      depth[y]++; // increment depth if both tree have the same depth
    }
    // update metadata for the merge set
    setSize[y] += setSize[x];
    maxElement[y] = std::max(maxElement[x], maxElement[y]);
    minElement[y] = std::min(minElement[x], maxElement[y]);
  }

  /**
   * @brief check if element `i` and `j` belong to the same set
   *
   * @param i first element
   * @param j second element
   * @return `true` if `i` and `j` are the same set, `false` otherwise
   */
  bool isSame(uint64_t i, uint64_t j) { return findSet(i) == findSet(j); }

  /**
   * @brief retrieve metadata for the set containing element `i`
   *
   * return vector containing the minimum element, max element, and size of the
   * set
   *
   * @param i element in the set
   * @return vector of size 3: [minElement, maxElement, setSize]
   */
  std::vector<uint64_t> get(uint64_t i) {
    std::vector<uint64_t> ans;
    ans.push_back(get_min(i)); // min element in the set
    ans.push_back(get_max(i)); // max element in the set
    ans.push_back(size(i));    // size of the set
    return ans;
  }

  /**
   * @brief get the max element in the set containing element `i`
   *
   * @param i element in the set
   * @return max element in the set containing `i`
   */
  uint64_t size(uint64_t i) { return setSize[findSet(i)]; }

  /**
   * @brief get the max element in the set containing element `i`
   *
   * @param i element in the set
   * @return max element in the set containing `i`
   */
  uint64_t get_max(uint64_t i) { return maxElement[findSet(i)]; }

  /**
   * @brief get the min element in the set containing element `i`
   *
   * @param i element in the set
   * @return min element in the set containing `i`
   */
  uint64_t get_min(uint64_t i) { return minElement[findSet(i)]; }

private:
  std::vector<uint64_t> p;          // parent pointer for each element
  std::vector<uint64_t> depth;      // depth of each set
  std::vector<uint64_t> setSize;    // size of each set
  std::vector<uint64_t> maxElement; // max element in each set
  std::vector<uint64_t> minElement; // min element in each set
};

#endif // !DSJOINT_SET_DJSOINT_SET_HPP
