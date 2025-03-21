#ifndef PLOT_ITERATOR_LIST_ITERATOR_HPP
#define PLOT_ITERATOR_LIST_ITERATOR_HPP

#include "link_list.hpp"
#include <memory>

/**
 * @class list_iter
 * @brief class representing an iterator for singly linked list
 *
 * this clas provide functionally to traverse singly linked list implemented
 * using `list_link` class
 *
 * @tparam T the type daa stored in the nodes of the linked list
 */
template <typename T>
class list_iter {
 public:
  /**
   * @brief default constructor for `list_iter`
   *
   * initialize the iterator with null pointer, representing an invalid or
   * end-of-list state
   */
  list_iter() noexcept {}
  /**
   * @brief parameterized constructor for `list_iter`
   *
   * initialize the iterator with a pointer to a specific node in the linked
   * list
   *
   * @param node shared pointer to the node in the linked list that this
   * iterator should point to
   */
  list_iter(const std::shared_ptr<list_link<T>> node) noexcept : curr(node) {}

  /**
   * @brief pre-increment operator
   *
   * advance the iterator to the next node in the linked list by updating the
   * internal pointer to the successor of the current node. if the current node
   * is null, the iterator remains unchanged
   *
   * @return list_iter& reference to the the update iterator
   */
  list_iter &operator++() {
    if (curr) {
      curr = curr->succ();
    }
    return *this;
  }

  /**
   * @brief post-increment operator
   *
   * create copy of the current iterator, advance the original iterator to the
   * next node, and return the copy, this will allow iterator to be used in
   * post-increment expression
   *
   * @return list_iter copy of the iterator before it was icremented
   */
  list_iter operator++(int) {
    list_iter it = *this;  // create copy of the current iterator
    ++*this;               // icrement the original iterator
    return it;             // return unmodified copy
  }

  /**
   * @brief inequality oeprator
   *
   * compare two iterator to determine if they are pointing to different nodes
   * in the linked list
   *
   * @param it the iterator to compare with
   * @return bool `true` if two iterators are not equal, `false` otherwise
   */
  bool operator!=(const list_iter &it) { return curr != it.curr; }

  /**
   * @brief deference operator
   *
   * retrieve the value stored in the node that the iterator is currently
   * pointing to
   *
   * @return T the value stored in the current node
   */
  T operator*() { return curr->val(); }

 private:
  /**
   * @brief a shared pointer to the current node in the linked list
   *
   * this pointer track the position of the iterator within the list, it is null
   * when the iterator representing the ned of the list or unitialized
   */
  std::shared_ptr<list_link<T>> curr;
};

#endif  // !PLOT_ITERATOR_LIST_ITERATOR_HPP
