#include <gtest/gtest.h>

#include "../enola/function/activation/relu.hpp"

TEST(ReluTest, HandlesEmptyInput) {
  std::vector<float> input           = {};
  std::vector<float> expected_output = {};
  std::vector<float> actual_output   = enola::function::relu(input);

  EXPECT_EQ(actual_output, expected_output);
}

TEST(ReluTest, HandlesSingleElement) {
  std::vector<float> input           = {-1.0f};
  std::vector<float> expected_output = {0.0f};
  std::vector<float> actual_output   = enola::function::relu(input);

  EXPECT_FLOAT_EQ(actual_output[0], expected_output[0]);
}

TEST(ReluTest, HandlesMultipleElements) {
  std::vector<double> input           = {-1.0, 0.0, 1.0, 2.0};
  std::vector<double> expected_output = {0.0, 0.0, 1.0, 2.0};
  std::vector<double> actual_output   = enola::function::relu(input);

  ASSERT_EQ(actual_output.size(), expected_output.size());
  for (size_t i = 0; i < actual_output.size(); ++i) {
    EXPECT_DOUBLE_EQ(actual_output[i], expected_output[i]);
  }
}

TEST(ReluTest, HandlesLargeValues) {
  std::vector<long double> input           = {-1e30L, 1e30L};
  std::vector<long double> expected_output = {0.0L, 1e30L};
  std::vector<long double> actual_output   = enola::function::relu(input);

  ASSERT_EQ(actual_output.size(), expected_output.size());
  for (size_t i = 0; i < actual_output.size(); ++i) {
    EXPECT_NEAR(actual_output[i], expected_output[i], 1e-5);
  }
}
