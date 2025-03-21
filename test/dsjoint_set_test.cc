#include "../enola/dsjoint_set/dsjoint_set.hpp"

#include <gtest/gtest.h>

TEST(DSUTest, Initialization) {
  dsu d1(5);

  for (uint64_t i = 0; i < 5; ++i) {
    EXPECT_EQ(d1.findSet(i), i);
  }

  for (uint64_t i = 0; i < 5; ++i) {
    EXPECT_EQ(d1.size(i), 1);
  }
}

TEST(DSUTest, FindSetWithPathCompression) {
  dsu d2(5);

  d2.UnionSet(0, 1);
  d2.UnionSet(1, 2);
  d2.UnionSet(2, 3);
  d2.UnionSet(3, 4);

  EXPECT_EQ(d2.findSet(0), 1);
  EXPECT_EQ(d2.findSet(1), 1);
  EXPECT_EQ(d2.findSet(3), 1);
}

TEST(DSUTest, IsSame) {
  dsu d3(5);

  EXPECT_FALSE(d3.isSame(0, 1));

  d3.UnionSet(0, 1);
  EXPECT_TRUE(d3.isSame(0, 1));

  EXPECT_FALSE(d3.isSame(0, 2));
}

TEST(DSUTest, GetMinMaxSize) {
  dsu d4(5);

  EXPECT_EQ(d4.get_min(0), 0);
  EXPECT_EQ(d4.get_max(0), 0);
  EXPECT_EQ(d4.size(0), 1);
}

TEST(DSUTest, AllElementsMerged) {
  dsu d5(5);

  for (uint64_t i = 0; i < 4; ++i) {
    d5.UnionSet(i, i + 1);
  }

  for (uint64_t i = 0; i < 5; ++i) {
    EXPECT_TRUE(d5.isSame(0, i));
  }

  EXPECT_EQ(d5.size(0), 5);
}
