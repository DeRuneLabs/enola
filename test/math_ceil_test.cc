#include <gtest/gtest.h>

#include "../enola/math/ceil.hpp"

TEST(CeilTest, ScalarValue) {
  EXPECT_EQ(enola::math::ceil(1.2f), 2);
  EXPECT_EQ(enola::math::ceil(-1.2f), -1);
  EXPECT_EQ(enola::math::ceil(-3.7), -3);
  EXPECT_EQ(enola::math::ceil(5), 5);
  EXPECT_EQ(enola::math::ceil(-10), -10);
  EXPECT_EQ(enola::math::ceil(0.0f), 0);
}

TEST(CeilTest, TensorValue) {
  std::vector<std::size_t>                          shape = {2, 3};
  enola::tensor::Storage<float, enola::tensor::CPU> tensor(shape);
  tensor[0] = 1.2f;
  tensor[1] = -3.7f;
  tensor[2] = 4.0f;
  tensor[3] = 5.9f;
  tensor[4] = -2.1f;
  tensor[5] = 0.0f;

  auto ceil_tensor = enola::math::ceil(tensor);

  EXPECT_EQ(ceil_tensor[0], 2);
  EXPECT_EQ(ceil_tensor[1], -3);
  EXPECT_EQ(ceil_tensor[2], 4);
  EXPECT_EQ(ceil_tensor[3], 6);
  EXPECT_EQ(ceil_tensor[4], -2);
  EXPECT_EQ(ceil_tensor[5], 0);
}

TEST(CeilTest, EmptyTensor) {
  std::vector<std::size_t> shape = {0};
  enola::tensor::Storage<float, enola::tensor::CPU> tensor(shape);

  auto ceil_tensor = enola::math::ceil(tensor);
  EXPECT_EQ(ceil_tensor.size(), 0);
}

