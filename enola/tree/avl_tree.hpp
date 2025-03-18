#ifndef TREE_AVL_TREE_HPP
#define TREE_AVL_TREE_HPP

/**
 * @file avl_tree.hpp
 * @brief implementation of avl tree (self balancing binary search tree)
 *
 * this file define `avl_tree` class template, which implements an AVL tree.
 * an AVL tree is a self-balancing binary search tree where the difference in
 * height of the left and right subtree is at most 1 for every node
 *
 * the class provide methods for inserting, removing, and traversing elements,
 * as well as maintaining the AVL balance property through rotations
 *
 * @tparam T type of data stored the AVL tree, must suppor comparsion operator *
 * An AVL tree is a self-balancing binary search tree where the difference in he
 */
#include <algorithm>
#include <cstdint>
#include <functional>
#include <vector>

template <typename T> class avl_tree {
public:
  /**
   * @brief default constructor
   * initialize an empty AVL tree with a null root
   */
  avl_tree() : root(nullptr) {}

  /**
   * @brief destructor
   * cleans up the AVL tree. currently does not explicitly delete nodes,
   * but can be extended to handle dynamic memory cleanup if needed
   */
  ~avl_tree() {}

  /**
   * @brief insert a new key into the AVL tree
   *
   * public method to insert a value into the tree. maintain the AVL property
   * by performing rotation if necessary after insertion
   *
   * @param key value to be inserted into the tree
   */
  void insert(T key) { root = __insert(root, key); }

  /**
   * @brief remove a key from the AVL tree
   *
   * public method to remove a value from the tree. maintaining the AVL property
   * by performing rotations if necessary after removal
   *
   * @param key value to be removed from the tree
   */
  void remove(T key) { root = __remove(root, key); }

  /**
   * @brief perform an inorder traversal of the AVL tree
   *
   * return vector containing the element of the tree in preorder order
   * preorder traversal visits nodes in the order: root, left subtree, right
   * subtree
   *
   * @return vector element in sorted order
   */
  std::vector<T> inorder() {
    std::vector<T> path;
    __inorder([&](node *callbacked) { path.push_back(callbacked->info); },
              root);
    return path;
  }

  /**
   * @brief perform a preorder traversal of the AVL tree
   *
   * return vector containing the element of the tree in preorder order
   * preorder traversal visits nodes in the order, root, left subtree, right
   * subtree
   *
   * @return vector element in preorder traversal order
   */
  std::vector<T> preorder() {
    std::vector<T> path;
    __preorder([&](node *callbacked) { path.push_back(callbacked->info); },
               root);
    return path;
  }

  /**
   * @brief perform postorder traversal of the AVL tree
   *
   * return vector containing the elements of the tree in postorder order
   * postorder traversal visits nodes in the order: left subtree, right subtree
   *
   * @return vector element in postorder traversal order
   */
  std::vector<T> postorder() {
    std::vector<T> path;
    __postorder([&](node *callbacked) { path.push_back(callbacked->info); },
                root);
    return path;
  }

private:
  /**
   * @struct node
   * @brief represent single node in the AVL tree
   *
   * each node contain the stored value, pointer to its left and right
   * and height of the substree rooted at this node
   */
  typedef struct node {
    T info;             // value stored in the node
    int64_t height;     // height of the node (for balancing)
    struct node *left;  // pointer to the left child
    struct node *right; // pointer to the right child
  } node;

  // pointer to the root of the AVL tree
  node *root;

  /**
   * @brief compute the height of node
   *
   * return the height of the subtree rooted at the given node
   * if the node is null returns 0
   *
   * @param root the node whose height is to be computed
   * @return the height of the subtree rooted at `root`
   */
  int64_t height(node *root) {
    return (root == nullptr)
               ? 0
               : 1 + std::max(height(root->left), height(root->right));
  }

  /**
   * @brief create new node with the given value
   *
   * allocate memory for new node, initialize its fields, and return a pointer
   * to it
   *
   * @param info the value to be stored in the new node
   * @return pointer to the newly created node
   */
  node *createNode(int info) {
    node *nn = new node();
    nn->info = info;
    nn->height = 0;
    nn->left = nullptr;
    nn->right = nullptr;
    return nn;
  }

  /**
   * @brief compute the balance factor node
   *
   * balance factor is the difference in height of the left and right subtree
   *
   * @param root the node whose balance factor is to be computed
   * @return balance factor fo the node
   */
  int64_t getBalance(node *root) {
    return height(root->left) - height(root->right);
  }

  /**
   * @brief perform right rotation on a node
   *
   * rotate given node to the right to restore the AVL property
   *
   * @param root the node to rotate
   * @return new root of the rotated substree
   */
  node *rightRotate(node *root) {
    node *t = root->left;
    node *u = t->right;
    t->right = root;
    root->left = u;
    return t;
  }

  /**
   * @brief perform a left rotation on a node
   *
   * rotate given node to the left to restore the AVL property
   *
   * @param root the node to rotate
   * @return new root of the rotated substree
   */
  node *leftRotate(node *root) {
    node *t = root->right;
    node *u = t->left;
    t->left = root;
    root->right = u;
    return t;
  }

  /**
   * @brief find the node with the minimum value in a substree
   *
   * traverse the left subtree to finding the node with the smallest value
   *
   * @param root root of the substree search
   * @return a  pointer to the node with the minimum value
   */
  node *minValue(node *root) {
    return (root->left == nullptr) ? root : minValue(root->left);
  }

  /**
   * @brief recursive helper function for insert key into the avl tree
   *
   * insert key into substree rooted at `root` and perform rotation
   * to maintain the AVL property
   *
   * @param root the root of the substree where the key is to be inserted
   * @param item value to be inserted
   * @return new root of the subtree after insertion and balancing
   */
  node *__insert(node *root, int item) {
    // base case create new node if the substree is empty
    if (root == nullptr) {
      return createNode(item);
    }

    // insert into the left or right substree based on comparsion
    if (item < root->info) {
      root->left = __insert(root->left, item);
    } else {
      root->right = __insert(root->right, item);
    }

    // update balance and perform rotation if necessary
    int b = getBalance(root);
    if (b > 1) {
      if (getBalance(root->left) < 0) {
        root->left = leftRotate(root->left); // left-right case
      }
      return rightRotate(root); // left-left case
    } else if (b < -1) {
      if (getBalance(root->right) > 0) {
        root->right = rightRotate(root->right); // right-left case
      }
      return leftRotate(root); // right-right case
    }
    return root;
  }

  /**
   * @brief recursive helper function for removing key from the AVL tree
   *
   * remove the key from the subtree rooted `root`, and perform rotation
   * to maintain the AVL property
   *
   * @param root the root of substree where the key is to be removed
   * @param key value to be removed
   * @return new root of the subtree after removal and balancing
   */
  node *__remove(node *root, int key) {
    if (root == nullptr) {
      return root;
    }

    // recursively search for the key to remov
    if (key < root->info) {
      root->left = __remove(root->left, key);
    } else if (key > root->info) {
      root->right = __remove(root->right, key);
    } else {
      // node with only one child or no child
      if (!root->right) {
        node *temp = root->left;
        delete (root);
        root = NULL;
        return temp;
      } else if (!root->left) {
        node *temp = root->right;
        delete (root);
        root = NULL;
        return temp;
      }

      // node with two child
      // get inorder sucessor
      node *temp = minValue(root->right);
      root->info = temp->info;
      root->right = __remove(root->right, temp->info);
    }
    return root;
  }

  /**
   * @brief recursive helper function for inorder traversal
   *
   * traverse substree rooted at `root` in inorder order, aplying the callback
   * function to each node visited
   *
   * @param callback function to apply to each node during traversal
   * @param root the root of the substree to traverse
   */
  void __inorder(std::function<void(node *)> callback, node *root) {
    if (root) {
      __inorder(callback, root->left);
      callback(root);
      __inorder(callback, root->right);
    }
  }

  /**
   * @brief recursive helper function for preorder traversal
   *
   * travese the subtree rooted at `root` in preorder order, applying the
   * callback to each node visited
   *
   * @param callback function to apply to each node during traversal
   * @param root root of the subtree to traverse
   */
  void __postorder(std::function<void(node *)> callback, node *root) {
    if (root) {
      __inorder(callback, root->left);
      __inorder(callback, root->right);
      callback(root);
    }
  }

  /**
   * @brief recursive helper function for postorder traversal
   *
   * traverse the subtree rooted at `root` in postorder order applying the
   * callback to each node visited
   *
   * @param callback a function to apply to each node during traversal
   * @param root root of the subtree to traverse
   */
  void __preorder(std::function<void(node *)> callback, node *root) {
    if (root) {
      callback(root);
      __inorder(callback, root->left);
      __inorder(callback, root->right);
    }
  }
};

#endif // !TREE_AVL_TREE_HPP
