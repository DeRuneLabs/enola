#include <gtest/gtest.h>

#include "../enola/function/activation/binary_step.hpp"
#include <stdexcept>

TEST(BinaryStepTest, HandleMixedValue) {
  std::vector<double> input    = {-1.2, 0, 2, 1.45, -3.7, 0.3};
  std::vector<int>    expected = {0, 1, 1, 1, 0, 1};
  auto result = enola::function::to_int_vector(enola::function::binary_step(input));

  EXPECT_EQ(result, expected);
}

TEST(BinaryStepTest, HandleAllNonNegativeValue) {
  std::vector<float> input    = {0.0f, 1.5f, 3.7f, 10.0f};
  std::vector<int>   expected = {1, 1, 1, 1};

  auto result = enola::function::to_int_vector(enola::function::binary_step(input));
  EXPECT_EQ(result, expected);
}

TEST(BinaryStepTest, HandleAllNegativeValue) {
  std::vector<int> input    = {-1, -2, -3, -4};
  std::vector<int> expected = {0, 0, 0, 0};

  std::vector<int> result = enola::function::binary_step(input);

  EXPECT_EQ(result, expected);
}

TEST(BinaryStepTest, HandleEmptyVector) {
  std::vector<double> input = {};
  EXPECT_THROW(enola::function::binary_step(input), std::invalid_argument);
}

TEST(BinaryStepTest, HandleIntegerInput) {
  std::vector<int> input    = {-5, 0, 10, -1};
  std::vector<int> expected = {0, 1, 1, 0};
  std::vector<int> result   = enola::function::binary_step(input);
  EXPECT_EQ(result, expected);
}
