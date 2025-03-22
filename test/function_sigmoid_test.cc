#include <gtest/gtest.h>

#include "../enola/function/sigmoid.hpp"
#include <vector>

TEST(SigmoidTest, HandlesEmptyInput) {
  std::vector<float> input           = {};
  std::vector<float> expected_output = {};
  std::vector<float> actual_output   = enola::function::sigmoid(input);

  EXPECT_EQ(actual_output, expected_output);
}

TEST(SigmoidTest, HandlesSingleElement) {
  std::vector<float> input           = {0.0f};
  std::vector<float> expected_output = {0.5f};
  std::vector<float> actual_output   = enola::function::sigmoid(input);

  EXPECT_FLOAT_EQ(actual_output[0], expected_output[0]);
}

TEST(SigmoidTest, HandlesMultipleElements) {
  std::vector<float> input           = {-1.0f, 0.0f, 1.0f, 2.0f};
  std::vector<float> expected_output = {0.268941f, 0.5f, 0.731059f, 0.880797f};
  std::vector<float> actual_output   = enola::function::sigmoid(input);

  ASSERT_EQ(actual_output.size(), expected_output.size());

  for (size_t i = 0; i < actual_output.size(); ++i) {
    EXPECT_NEAR(actual_output[i], expected_output[i], 1e-5);
  }
}

TEST(SigmoidTest, HandlesLargeValues) {
  std::vector<float> input           = {-100.0f, 100.0f};
  std::vector<float> expected_output = {0.0f, 1.0f};
  std::vector<float> actual_output   = enola::function::sigmoid(input);

  ASSERT_EQ(actual_output.size(), expected_output.size());
  for (size_t i = 0; i < actual_output.size(); ++i) {
    EXPECT_NEAR(actual_output[i], expected_output[i], 1e-5);
  }
}
