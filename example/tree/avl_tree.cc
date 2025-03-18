#include "../../enola/tree/avl_tree.hpp"
#include <iostream>

int main() {
  avl_tree<int> tree;

  std::cout << "Inserting elements: 10, 20, 30, 40, 50\n";
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  tree.insert(40);
  tree.insert(50);

  std::cout << "inorder traversal: ";
  std::vector<int> inorder_result = tree.inorder();
  for (int value : inorder_result) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  std::cout << "preorder traversal: ";
  std::vector<int> preorder_result = tree.preorder();
  for (int value : preorder_result) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  std::cout << "postorder traversal: ";
  std::vector<int> postorder_result = tree.postorder();
  for (int value : postorder_result) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  std::cout << "remove element 20" << std::endl;
  tree.remove(20);

  std::cout << "inorder traversal after removeing 20: ";
  inorder_result = tree.inorder();
  for (int value : inorder_result) {
    std::cout << value << " ";
  }
  std::cout << std::endl;

  std::cout << "attempting remove non-existent element 60" << std::endl;
  tree.remove(60);

  std::cout << "inorder traversal after attempting to remove 60: ";
  inorder_result = tree.inorder();
  for (int value : inorder_result) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}
