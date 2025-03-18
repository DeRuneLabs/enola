#include "../../enola/tree/bintree.hpp"
#include <iostream>

int main() {
  bintree<int> tree;

  std::cout << "Inserting elements: 50, 30, 70, 20, 40, 60, 80\n";
  tree.insert(50); // root node
  tree.insert(30); // left child of root
  tree.insert(70); // right child of root
  tree.insert(20); // left child of 30
  tree.insert(40); // right child of 30
  tree.insert(60); // left child of 70
  tree.insert(80); // right child of 70

  // perform in-order traversal
  std::cout << "\nIn-Order Traversal (sorted order): ";
  std::vector<int> inorder_result = tree.inorder();
  for (int value : inorder_result) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // remove a leaf node
  std::cout << "\nRemoving leaf node 20...\n";
  tree.remove(20);
  std::cout << "In-Order Traversal after removal: ";
  inorder_result = tree.inorder();
  for (int value : inorder_result) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // remove a node with one child
  std::cout << "\nRemoving node 30 (with one child)...\n";
  tree.remove(30);
  std::cout << "In-Order Traversal after removal: ";
  inorder_result = tree.inorder();
  for (int value : inorder_result) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // remove a node with two children
  std::cout << "\nRemoving node 70 (with two children)...\n";
  tree.remove(70);
  std::cout << "In-Order Traversal after removal: ";
  inorder_result = tree.inorder();
  for (int value : inorder_result) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  // remove the root node
  std::cout << "\nremoving root node 50...\n";
  tree.remove(50);
  std::cout << "in-Order Traversal after removal: ";
  inorder_result = tree.inorder();
  for (int value : inorder_result) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  return 0;
}
