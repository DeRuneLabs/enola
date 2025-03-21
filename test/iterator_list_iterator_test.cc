#include <gtest/gtest.h>

#include "../enola/plot/iterator/list_iterator.hpp"

TEST(ListIterTest, DefaultConstructor) {
  list_iter<int> iter;

  EXPECT_EQ(iter != list_iter<int>(), false);
}

TEST(ListIterTest, ParameterizedConstructor) {
  auto           node = std::make_shared<list_link<int>>(42);
  list_iter<int> iter(node);

  EXPECT_EQ(*iter, 42);
}

TEST(ListIterTest, PreIncrementOperator) {
  auto node_1    = std::make_shared<list_link<int>>(10);
  auto node_2    = std::make_shared<list_link<int>>(20);
  node_1->succ() = node_2;

  list_iter<int> iter(node_1);
  ++iter;
  EXPECT_EQ(*iter, 20);

  ++iter;
  EXPECT_EQ(iter != list_iter<int>(), false);
}

TEST(ListIterTest, PostIncementOperator) {
  auto node_1    = std::make_shared<list_link<int>>(10);
  auto node_2    = std::make_shared<list_link<int>>(20);
  node_1->succ() = node_2;

  list_iter<int> iter(node_1);
  list_iter<int> old_iter = iter++;
  EXPECT_EQ(*old_iter, 10);
  EXPECT_EQ(*iter, 20);
}

TEST(ListIterTest, InequalityOperator) {
  auto           node_1 = std::make_shared<list_link<int>>(10);
  auto           node_2 = std::make_shared<list_link<int>>(20);
  list_iter<int> iter1(node_1);
  list_iter<int> iter2(node_2);
  iter1 = list_iter<int>();
  iter2 = list_iter<int>();
  EXPECT_EQ(iter1 != iter2, false);
}

TEST(ListIterTest, DereferenceOperator) {
  auto           node = std::make_shared<list_link<int>>(42);
  list_iter<int> iter(node);

  EXPECT_EQ(*iter, 42);
}
