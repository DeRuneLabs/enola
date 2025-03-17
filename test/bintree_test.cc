#include "../enola/tree/bintree.hpp"
#include <gtest/gtest.h>

TEST(BintreeTests, Constructor) {
  bintree<int> tree;
  EXPECT_NO_THROW(tree.insert(50));
  EXPECT_NO_THROW(tree.insert(30));
  EXPECT_NO_THROW(tree.insert(70));
}

TEST(BintreeTests, Insert) {
  bintree<int> tree;
  EXPECT_NO_THROW(tree.insert(50));
  EXPECT_NO_THROW(tree.insert(30));
  EXPECT_NO_THROW(tree.insert(70));
}

TEST(BintreeTests, InOrderTraversal) {
  bintree<int> tree;
  tree.insert(50);
  tree.insert(30);
  tree.insert(70);
  tree.insert(20);
  tree.insert(40);
  tree.insert(60);
  tree.insert(80);

  std::vector<int> expected_inorder = {20, 30, 40, 50, 60, 70, 80};
  EXPECT_EQ(tree.inorder(), expected_inorder);
}
