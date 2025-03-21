#include <gtest/gtest.h>

#include "../enola/list/linked_list.hpp"

TEST(LinkedListTest, IsEmptyInitially) {
  linked_list<int> list;
  EXPECT_TRUE(list.empty());
}

TEST(LinkedListTest, PushBackElements) {
  linked_list<int> list;

  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  EXPECT_FALSE(list.empty());
}

TEST(LinkedListTest, PushFrontElements) {
  linked_list<int> list;

  list.push_front(30);
  list.push_front(20);
  list.push_front(10);

  EXPECT_FALSE(list.empty());
}

TEST(LinkedListTest, SearchElement) {
  linked_list<int> list;

  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  auto found = list.search(20);
  EXPECT_NE(found, nullptr);
  EXPECT_EQ(found->val(), 20);

  auto not_found = list.search(50);
  EXPECT_EQ(not_found, nullptr);
}
