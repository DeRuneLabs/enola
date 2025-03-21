#ifndef LIST_LINKED_LIST_HPP
#define LIST_LINKED_LIST_HPP

#include "../plot/iterator/list_iterator.hpp"
#include <iostream>
#include <ostream>
#include <stdexcept>

template <typename T> class linked_list {
public:
  explicit linked_list()
      : root(std::make_shared<list_link<T>>()), tail(nullptr) {}
  bool empty() { return tail == nullptr; }
  list_iter<T> begin() { return list_iter<T>(root); }
  list_iter<T> end() { return list_iter<T>(nullptr); }

  void push_back(T key) {
    if (empty()) {
      root->succ() = std::make_shared<list_link<T>>(key);
      tail = root->succ();
    } else {
      tail->succ() = std::make_shared<list_link<T>>(key);
      tail = tail->succ();
    }
  }

  void push_front(T key) {
    if (empty()) {
      root->succ() = std::make_shared<list_link<T>>(key);
      tail = root->succ();
    } else {
      std::shared_ptr<list_link<T>> p = std::make_shared<list_link<T>>(key);
      p->succ() = root->succ();
      root->succ() = p;
    }
  }

  void erase(T key) {
    if (empty()) {
      return;
    }
    std::shared_ptr<list_link<T>> t = root;
    std::shared_ptr<list_link<T>> to_be_removed = nullptr;
    while (t != tail && t->succ()->val() != key) {
      t = t->succ();
    }
    if (t == tail) {
      return;
    }
    to_be_removed = t->succ();
    t->succ() = t->succ()->succ();
    to_be_removed.reset();
    if (t->succ() == nullptr) {
      tail = t;
    }
    if (root == tail) {
      tail == nullptr;
    }
  }

  std::shared_ptr<list_link<T>> search(T key) {
    try {
      if (empty()) {
        throw std::invalid_argument("list was empty");
      } else {
        std::shared_ptr<list_link<T>> t = root;
        while (t != tail && t->succ()->val() != key) {
          t = t->succ();
        }
        if (t == tail) {
          return nullptr;
        }
        return t->succ();
      }
    } catch (std::invalid_argument &error) {
      std::cerr << error.what() << "\n";
      return nullptr;
    }
  }

  friend constexpr std::ostream &operator<<(std::ostream &out,
                                            linked_list<T> &l1);
  friend constexpr linked_list &operator+(const linked_list<list_link<T>> &l1,
                                          const linked_list<list_link<T>> &l2);

private:
  std::shared_ptr<list_link<T>> root;
  std::shared_ptr<list_link<T>> tail;
};

#endif // !LIST_LINKED_LIST_HPP
