#ifndef TREE_BINTREE_HPP
#define TREE_BINTREE_HPP

#include <cstdint>
#include <functional>
#include <queue>
#include <vector>

/**
 * @brief generic binary search tree implementation
 *
 * this class provides a binary tree data structure with methods to insert,
 * remove, and traversal nodes. support common traversal techniques such as
 * level-order, in-order, pre-order, and post-orderd traversal
 *
 * @tparam T type of data stored in the binary tree nodes. must supporting
 * comparison operator
 * (<, >)
 */
template <typename T> class bintree {
public:
  /**
   * @brief default constructor for binary tree
   *
   * initialize an empty binary tree with the root set to `nullptr`
   */
  bintree() : root(nullptr) {}

  /**
   * @brief destructor for the binary tree
   *
   * clean up all dynamically allocated memory used by the tree nodes
   */
  ~bintree() {}

  /**
   * @brief insert a new node with the given key into the binary tree
   *
   * the insert follow the binary search tree property:
   * - if the key is less than the current node's value, it goes to the left
   * subtree
   * - if the key is greater than or equal to the current node's value, it goes
   * to the right subtree
   *
   * @param key value to be inserted into the tree
   */
  void insert(T key) { root = __insert(root, key); }

  /**
   * @brief remove node with the given key from the binary tree
   *
   * handle three case:
   * - node has no childern: simply delete the node
   * - node has one chold: replace the node with its child
   * - node has two child: find the in-order successor (smallest node in the
   * right subtree), replace the node's value with the successor's value, and
   * then delete the successor
   *
   * @param key value the be removed from the tree
   */
  void remove(T key) { root = __remove(root, key); }

  /**
   * @brief perform level-order traversal of the binary-tree
   *
   * level-order visit nodes level by level, starting from the root
   * this implementation uses a queue to process nodes in breadth-first order
   *
   * @return vector of vector, where each inner vector contains the values of
   * nodes at a specific level
   */
  std::vector<std::vector<T>> level_order() {
    std::vector<std::vector<T>>
        levels; // store the resut of level-order traversak
    if (!root) {
      return levels; // return empty if the tree is empty
    }
    std::queue<T> q; // queue to facilitate breadth-first traversal

    q.push(root);
    while (!q.empty()) {
      int64_t size = q.size(); // number of node at the current the level
      std::vector<T> row;      // temporary storage for the current level node

      for (int64_t i = 0; i < size; i++) {
        T current = q.front();
        row.push_back(current);
        q.pop();

        if (current->right) {
          q.push(current->right);
        }

        if (current->left) {
          q.push(current->left);
        }
      }
      levels.push_back(row); // add the current level node to the result
    }
    return levels;
  }

  /**
   * @brief perform an in-order traversal of the binary tree
   *
   * in-order traversal visits nodes in the following order:
   * - traverse the left subtree
   * - visit the current node
   * - traverse the right subtree
   *
   * @return vector containing the value of node in in-order sequence
   */
  std::vector<T> inorder() {
    std::vector<T> path;
    __inorder([&](node *callbacked) { path.push_back(callbacked->info); },
              root);
    return path;
  }

  /**
   * @brief perform pre-order traversal of the binary-tree
   *
   * pre-order traversal visits nodes in the following order:
   * - visist the current node
   * - traverse the left subtree
   * - traverse the right subtree
   *
   * @return vector containing the value of node in pre-order sequence
   */
  std::vector<T> preorder() {
    std::vector<T> path; // store result of pre-order traversal
    __preorder([&](node *callbacked) { path.push_back(callbacked->info); },
               root);
    return path;
  }

  /**
   * @brief perform post-orderd traversal of the binary tree
   *
   * post-orderd traversal visit nodes in the following order:
   * - traverse the left subtree
   * - traverse the right subtree
   * - visit the current node
   *
   * @return vector containing the value of nodes in post-order sequence
   */
  std::vector<T> postorder() {
    std::vector<T> path; // store result of post-order traversal
    __postorder([&](node *callbacked) { path.push_back(callbacked->info); },
                root);
    return path;
  }

private:
  /**
   * @brief represent single node in the binary tree
   *
   * each node contain
   * - `info`: value stored in the node
   * - `left`: pointer to the left child node
   * -  `right`: pointer to the right child node
   */
  struct node {
    T info;             // value stored in the node
    node *right, *left; // pointer to right and left child
  };

  node *root; // pointer to the root node of the binary tree

  /**
   * @brief create new node with the given key
   *
   * allocate memory for new node, initialize its value, and sets it
   * left and right pointer to `nullptr`
   *
   * @param key value to be stored in the new node
   * @return pointer to the newly created node
   */
  node *new_node(T &key) {
    node *p = new node;
    p->info = key;
    p->right = p->left = nullptr;
    return p;
  }

  /**
   * @brief recursively insert new node into the binary tree
   *
   * follow the binary search tree property to determine the correct position
   * for the new node
   *
   * @param node current root of the subtree being processed
   * @param key value to be inserted
   * @return update root of the subtree after insertion
   */
  node *__insert(node *root, T &key) {
    if (!root) {
      return new_node(key);
    } else {
      if (root->info < key) {
        root->right = __insert(root->right, key);
      } else {
        root->left = __insert(root->left, key);
      }
    }
    return root;
  }

  /**
   * @brief recursively remove node with the given key from the binary tree
   *
   * handle different cases based on the number of childern of the node to be
   * removed
   *
   * @param root current root of the subtree being processed
   * @param key value to be removed
   * @return update root of the subtree after removal
   */
  node *__remove(node *root, T &key) {
    if (!root) {
      return root;
    }

    if (root->info < key) {
      root->right = __remove(root->right, key);
    } else if (root->info > key) {
      root->left = __remove(root->left, key);
    } else {
      if (!root->left && !root->right) {
        delete root;
        root = nullptr;
      } else if (!root->left) {
        node *temp = root->right;
        delete root;
        return temp;
      } else if (!root->right) {
        node *temp = root->left;
        delete root;
        return temp;
      } else {
        node *temp = root->right;
        while (temp->left) {
          temp = temp->left;
        }
        root->info = temp->info;
        root->right = __remove(root->right, temp->info);
      }
    }
    return root;
  }

  /**
   * @brief recursively perform in-order traversal of the binary-tree
   * 
   * applies the provide callback function to each node in in-order sequence
   * 
   * @param callback function to be applied to each node during traversal
   * @param root current root of the subtree being processed
  */
  void __inorder(std::function<void(node *)> callback, node *root) {
    if (root) {
      __inorder(callback, root->left);
      callback(root);
      __inorder(callback, root->right);
    }
  }

  /**
   * @brief recursively perform post-order traversal of the binary-tree
   * 
   * applies the provided callback function to each node in post-order sequence
   *
   * @param callback function to be applied to each node during traversal
   * @param root current root of the subtree being processed
  */
  void __postorder(std::function<void(node *)> callback, node *root) {
    if (root) {
      __inorder(callback, root->left);
      __inorder(callback, root->right);
      callback(root);
    }
  }

  /**
   * @brief recursively perform pre-order traversal of the binary-tree
   *
   * applies the provided callback function to each node in pre-order sequence
   *
   * @param callback function to be applied to each node during traversal
   * @param root current root of the subtree being processed
  */
  void __preorder(std::function<void(node *)> callback, node *root) {
    if (root) {
      callback(root);
      __inorder(callback, root->left);
      __inorder(callback, root->right);
    }
  }
};

#endif // !TREE_BINTREE_HPP
