#include <gtest/gtest.h>

#include "../enola/math/abs.hpp"

TEST(AbsTest, PositiveInteger) {
  std::vector<std::size_t>                        shape = {3};
  enola::tensor::Storage<int, enola::tensor::CPU> tensor(shape);

  tensor[0]   = 1;
  tensor[1]   = 2;
  tensor[2]   = 3;
  auto result = enola::math::abs(tensor);

  EXPECT_EQ(result[0], 1);
  EXPECT_EQ(result[1], 2);
  EXPECT_EQ(result[2], 3);
}

TEST(AbsTest, NegativeInteger) {
  std::vector<std::size_t>                        shape = {3};
  enola::tensor::Storage<int, enola::tensor::CPU> tensor(shape);

  tensor[0] = -1;
  tensor[1] = -2;
  tensor[2] = -3;

  auto result = enola::math::abs(tensor);
  EXPECT_EQ(result[0], 1);
  EXPECT_EQ(result[1], 2);
  EXPECT_EQ(result[2], 3);
}

TEST(AbsTest, FloatingPointNumber) {
  std::vector<std::size_t>                           shape = {3};
  enola::tensor::Storage<double, enola::tensor::CPU> tensor(shape);

  tensor[0] = -1.5;
  tensor[1] = 2.75;
  tensor[2] = -3.25;

  auto result = enola::math::abs(tensor);
  EXPECT_DOUBLE_EQ(result[0], 1.5);
  EXPECT_DOUBLE_EQ(result[1], 2.75);
  EXPECT_DOUBLE_EQ(result[2], 3.25);
}
