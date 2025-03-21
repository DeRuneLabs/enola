#include <gtest/gtest.h>

#include "../enola/plot/iterator/link_list.hpp"
#include <memory>

TEST(ListLinkTest, ConstructorAndAccessor) {
  list_link<int> node_1;

  EXPECT_EQ(node_1.val(), 0);
  EXPECT_EQ(node_1.succ(), nullptr);

  list_link<int> node_2(42);
  EXPECT_EQ(node_2.val(), 42);
  EXPECT_EQ(node_2.succ(), nullptr);

  auto nextNode = std::make_shared<list_link<int>>(84);
  node_2.succ() = nextNode;
  EXPECT_EQ(node_2.succ()->val(), 84);
}

TEST(ListLinkTest, MutabilityOfSuccessor) {
  list_link<int> node_1(10);
  auto           node_2 = std::make_shared<list_link<int>>(20);

  node_1.succ() = node_2;

  EXPECT_EQ(node_1.succ()->val(), 20);
}

TEST(DoubleLinkTest, ConstructorAndAccessor) {
  double_link<int> node_1;
  EXPECT_EQ(node_1.val(), 0);
  EXPECT_EQ(node_1.succ(), nullptr);
  EXPECT_EQ(node_1.prev(), nullptr);
}

TEST(DoubleLinkTest, MutabilityOfSuccessorAndPrecedessor) {
  double_link<int> node_1(10);
  auto             node_2 = std::make_shared<double_link<int>>(20);
  auto             node_3 = std::make_shared<double_link<int>>(30);

  node_1.succ()  = node_2;
  node_2->prev() = std::make_shared<double_link<int>>(node_1);
  node_2->succ() = node_3;
  node_3->prev() = node_2;

  EXPECT_EQ(node_1.succ()->val(), 20);
  EXPECT_EQ(node_2->prev()->val(), 10);
  EXPECT_EQ(node_2->succ()->val(), 30);
  EXPECT_EQ(node_3->prev()->val(), 20);
}

TEST(DoubleLinkTest, CircularLinking) {
  auto node_1 = std::make_shared<double_link<int>>(10);
  auto node_2 = std::make_shared<double_link<int>>(20);

  node_1->succ() = node_2;
  node_2->prev() = node_1;
  node_2->succ() = node_1;
  node_1->prev() = node_2;

  EXPECT_EQ(node_1->succ()->val(), 20);
  EXPECT_EQ(node_2->succ()->val(), 10);
  EXPECT_EQ(node_2->succ()->val(), 10);
  EXPECT_EQ(node_1->prev()->val(), 20);
}
