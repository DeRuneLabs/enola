#ifndef LIST_LINKED_LIST_HPP
#define LIST_LINKED_LIST_HPP

#include "../plot/iterator/list_iterator.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>

/**
 * @brief template linked list implementation
 *
 * this class provide simple implementation of single linked list with
 * methods to add elements, remove element, search element and iterater over the
 * list
 */
template <typename T>
class linked_list {
 public:
  /**
   * @brief default constructor
   *
   * initialize an empty linked list, the `root` node is created as dummy
   * sentinel node, and `tail` is set to `nullptr` to indicate the list
   * was empty
   */
  explicit linked_list()
      : root(std::make_shared<list_link<T>>()), tail(nullptr) {}

  /**
   * @brief check if list was empty
   *
   * @return `true` if list was empty, `false` otherwise
   */
  bool empty() { return tail == nullptr; }

  /**
   * @brief return an iterator pointing to the begining of the list
   *
   * @return iterator starting at the first actual node
   */
  list_iter<T> begin() { return list_iter<T>(root); }

  /**
   * @brief return an iterator pointing to the end of the list
   *
   * @return iterator representing the of the list
   */
  list_iter<T> end() { return list_iter<T>(nullptr); }

  /**
   * @brief add an element to the back of the list
   *
   * if the list empty, the new element become the first node after dummy root
   * otherwise, it appends the new node to the end of the list update the tail
   *
   * @param key the value to be added to the list
   */
  void push_back(T key) {
    if (empty()) {
      root->succ() = std::make_shared<list_link<T>>(key);
      tail         = root->succ();
    } else {
      tail->succ() = std::make_shared<list_link<T>>(key);
      tail         = tail->succ();
    }
  }

  /**
   * @brief add an element to the front of the list
   *
   * if the list empty, the new element become the first node after the dummy
   * `root` otherwise, it inserts the new node after `root` and adjusts the
   * links accordingly
   *
   * @param key the value ot be added to the list
   */
  void push_front(T key) {
    if (empty()) {
      root->succ() = std::make_shared<list_link<T>>(key);
      tail         = root->succ();
    } else {
      std::shared_ptr<list_link<T>> p = std::make_shared<list_link<T>>(key);
      p->succ()                       = root->succ();
      root->succ()                    = p;
    }
  }

  /**
   * @brief remove the first occurence of a given value from the list
   *
   * searches for the node containing the specified value and remove it
   * if the value is not found, the list remains unchanged
   *
   * @param key the value to be removed from the list
   */
  void erase(T key) {
    if (empty()) {
      return;
    }
    std::shared_ptr<list_link<T>> t             = root;
    std::shared_ptr<list_link<T>> to_be_removed = nullptr;
    // traverse the list to find the node toe be removed
    while (t != tail && t->succ()->val() != key) {
      t = t->succ();
    }
    // if value was not found, return
    if (t == tail) {
      return;
    }
    // remove the node
    to_be_removed = t->succ();
    t->succ()     = t->succ()->succ();
    to_be_removed.reset();
    // update the tail if necessary
    if (t->succ() == nullptr) {
      tail = t;
    }
    // handle edge case where the list becomes empty
    if (root == tail) {
      tail == nullptr;
    }
  }

  /**
   * @brief search for a gven value in the list
   *
   * traverse the list to find the first node containing the specified value
   * if the list empty or the value is not found, return `nullptr`
   *
   * @param key the value to search for
   * @return pointer to the node containing the value, `nullptr` if not found
   */
  std::shared_ptr<list_link<T>> search(T key) {
    try {
      if (empty()) {
        throw std::invalid_argument("list was empty");
      } else {
        std::shared_ptr<list_link<T>> t = root;
        // traverse the lit to find the node with the given value
        while (t != tail && t->succ()->val() != key) {
          t = t->succ();
        }
        // if the value was not found, return nullptr
        if (t == tail) {
          return nullptr;
        }
        // return node containing the value
        return t->succ();
      }
    } catch (std::invalid_argument &error) {
      std::cerr << error.what() << "\n";
      return nullptr;
    }
  }

  /**
   * @brief overload the output stream oeprator to print the list
   *
   * allow printing the content of list
   *
   * @param out the output stream
   * @param l1 the linked list to be printed
   * @return output stream with the list contents append
   */
  friend std::ostream &operator<<(std::ostream   &out,
                                            linked_list<T> &l1) {
    out << "[";
    auto it = l1.begin();
    while (it != l1.end()) {
      out << *it;
      ++it;
      if (it != l1.end()) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  /**
   * @brief overloaded the addition operator to concatenate two list
   *
   * concatenate two linked list into single list
   *
   * @param l1 first linked list
   * @param l2 second linked list
   * @return new linked list containing the concatenated element
   */
  friend constexpr linked_list &operator+(const linked_list<list_link<T>> &l1,
                                          const linked_list<list_link<T>> &l2);

 private:
  /**
   * @brief shared pointer to the dummy root node of the list
   *
   * acts as sentinel node to simplify list operation
   */
  std::shared_ptr<list_link<T>> root;
  /**
   * @brief shared pointer to the last node in the list
   *
   * point to the tail of the list, if the list empty, this is `nullptr`
   */
  std::shared_ptr<list_link<T>> tail;
};

#endif  // !LIST_LINKED_LIST_HPP
