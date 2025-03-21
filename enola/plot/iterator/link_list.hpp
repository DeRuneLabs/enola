#ifndef PLOT_ITERATOR_LIST_LINK_HPP
#define PLOT_ITERATOR_LIST_LINK_HPP

#include <memory>

/**
 * @class list_link
 * @brief class representing single node in single linked list
 *
 * this class encapsulate the value stored in the node and pointer to the next
 * node in the list
 *
 * @tparam T the type of data store in the node
 */
template <typename T>
class list_link {
 public:
  /**
   * @brief constructor for the `list_link`
   *
   * initialize node with given value and set the successor pointer to the
   * `nullptr`
   *
   * @param value the value to be stored in the node, default `0` if not
   * provided
   */
  explicit list_link(T value = 0) : pvalue(value), psucc(nullptr) {}
  /**
   * @brief retrieve the value stored in the node
   *
   * @return T the value stored in the node
   */
  T val() { return pvalue; }

  /**
   * @brief retrieve refernce the shared pointer pointing to the successor node
   *
   * this allow modification of the successor node or traversal of the list
   *
   * @return std::shared_ptr<list_link>& reference to the shared pointer of the
   * successor
   */
  std::shared_ptr<list_link> &succ() { return psucc; }

 private:
  T                          pvalue;  // value to stored in the node
  std::shared_ptr<list_link> psucc;   // pointer to the nex node in the list
};

/**
 * @class double_link
 * @brief class representing single node in double linked list
 *
 * this class extend functionaliyy of `list_link` by adding pointer to the
 * previous node in addition to the successor node
 *
 * @tparam the type of data stored in the node
 */
template <typename T>
class double_link {
 public:
  /**
   * @brief constructor `double_link`
   *
   * initialize the node with given value and sets both the successor and
   * precedessor pointer to the `nullptr`
   *
   * @param value the value to be stored in the node. default `0` if not
   * provided
   */
  explicit double_link(T value = 0)
      : pvalue(value), psucc(nullptr), pprev(nullptr) {}

  /**
   * @brief retrieve value stored in the node
   *
   * @return T the value stored in the node
   */
  T val() { return pvalue; }

  /**
   * @brief referieve reference to the shared pointing to the successor node
   *
   * this allow modification of the succesor node or forward traversal of the
   * list
   *
   * @return std::shared_ptr<double_link>& reference to the shared pointer
   */
  std::shared_ptr<double_link> &succ() { return psucc; }
  /**
   * @brief retrieve reference to the shared pointer pointing to the precedessor
   * node
   *
   * this allow modification of the precedessor node or backward traversal of
   * the list
   *
   * @return std::shard_ptr<double_link>& reference to the shared pointer of the
   * precedessor
   */
  std::shared_ptr<double_link> &prev() { return pprev; }

 private:
  T                            pvalue;  // value stored in the  node
  std::shared_ptr<double_link> psucc;   // pointer to the next node in the list
  std::shared_ptr<double_link>
      pprev;  // pointer to the previous node in the list
};

#endif  // !PLOT_ITERATOR_LIST_LINK_HPP
