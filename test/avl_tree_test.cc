#include "../enola/tree/avl_tree.hpp"

#include <gtest/gtest.h>

#include <vector>

TEST(AVLTreeTests, InsertAndTraverse) {
  avl_tree<int> tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  tree.insert(40);
  tree.insert(50);

  std::vector<int> inorder_result = tree.inorder();
  EXPECT_EQ(inorder_result, std::vector<int>({10, 20, 30, 40, 50}));

  std::vector<int> preorder_result = tree.preorder();
  EXPECT_EQ(preorder_result, std::vector<int>({20, 10, 30, 40, 50}));

  std::vector<int> postorder_result = tree.postorder();
  EXPECT_EQ(postorder_result, std::vector<int>({10, 30, 40, 50, 20}));
}

TEST(AVLTreeTests, RemoveElements) {
  avl_tree<int> tree;

  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  tree.insert(40);
  tree.insert(50);

  tree.remove(20);

  std::vector<int> inorder_result = tree.inorder();
  EXPECT_EQ(inorder_result, std::vector<int>({10, 30, 40, 50}));

  tree.remove(40);

  inorder_result = tree.inorder();
  EXPECT_EQ(inorder_result, std::vector<int>({10, 30, 50}));
}

TEST(AVLTreeTests, EdgeCases) {
  avl_tree<int> tree;

  std::vector<int> inorder_result = tree.inorder();
  EXPECT_TRUE(inorder_result.empty());

  tree.insert(10);
  tree.insert(10);
  inorder_result = tree.inorder();
  EXPECT_EQ(inorder_result, std::vector<int>({10, 10}));

  tree.remove(10);
  inorder_result = tree.inorder();
  EXPECT_EQ(inorder_result, std::vector<int>({10}));
}

TEST(AVLTreeTests, BalanceMaintenance) {
  avl_tree<int> tree;

  tree.insert(30);
  tree.insert(20);
  tree.insert(10);

  std::vector<int> inorder_result = tree.inorder();
  EXPECT_EQ(inorder_result, std::vector<int>({10, 20, 30}));

  tree.insert(40);
  tree.insert(50);

  inorder_result = tree.inorder();
  EXPECT_EQ(inorder_result, std::vector<int>({10, 20, 30, 40, 50}));
}
