#include <gtest/gtest.h>

#include "../enola/ops/deep_copy.hpp"
#include <memory>

TEST(DeepCopyTest, IntegerDeepCopy) {
  int orig   = 42;
  int copied = enola::ops::DeepCopy(orig);

  EXPECT_EQ(copied, orig);
  orig = 100;
  EXPECT_NE(copied, orig);
}

TEST(DeepCopyTest, VectorDeepCopy) {
  std::vector<int> orig   = {1, 2, 3};
  std::vector<int> copied = enola::ops::DeepCopy(orig);

  EXPECT_EQ(copied.size(), orig.size());
  for (size_t i = 0; i < orig.size(); ++i) {
    EXPECT_EQ(copied[i], orig[i]);
  }

  orig.push_back(4);
  EXPECT_NE(copied.size(), orig.size());
}

TEST(DeepCopyTest, SharedPtrDeepCopy) {
  auto orig   = std::make_shared<int>(42);
  auto copied = enola::ops::DeepCopy(orig);

  EXPECT_NE(copied, orig);
  EXPECT_EQ(*copied, *orig);

  *orig = 100;
  EXPECT_NE(*copied, *orig);
}

TEST(DeepCopyTest, NullSharedPtrDeepCopy) {
  std::shared_ptr<int> orig = nullptr;
  auto copied = enola::ops::DeepCopy(orig);
  
  EXPECT_EQ(copied, nullptr);
}
