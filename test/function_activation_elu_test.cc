#include <gtest/gtest.h>

#include "../enola/function/activation/elu.hpp"
#include <cmath>

TEST(ELUTest, PositiveValueOnly) {
  std::vector<float> input           = {1.0f, 2.5f, 3.0f};
  float              alpha           = 0.5f;
  std::vector<float> expected_output = {1.0f, 2.5f, 3.0f};

  std::vector<float> output =
      enola::function::exponential_linear_unit(input, alpha);
  EXPECT_EQ(output.size(), expected_output.size());
  for (size_t i = 0; i < output.size(); ++i) {
    EXPECT_FLOAT_EQ(output[i], expected_output[i]);
  }
}

TEST(ELUTest, NegativeValue) {
  std::vector<float> input           = {-1.0f, -2.0f, -3.0f};
  float              alpha           = 0.5f;
  std::vector<float> expected_output = {0.5f * (std::exp(-1.0f) - 1),
                                        0.5f * (std::exp(-2.0f) - 1),
                                        0.5f * (std::exp(-3.0f) - 1)};
  std::vector<float> output =
      enola::function::exponential_linear_unit(input, alpha);
  EXPECT_EQ(output.size(), expected_output.size());
  for (size_t i = 0; i < output.size(); ++i) {
    EXPECT_FLOAT_EQ(output[i], expected_output[i]);
  }
}

TEST(ELUTest, MixValue) {
  std::vector<float> input           = {1.0f, -1.0f, 2.0f, -2.0f};
  float              alpha           = 0.3f;
  std::vector<float> expected_output = {
      1.0f, 0.3f * (std::exp(-1.0f) - 1), 2.0f, 0.3f * (std::exp(-2.0f) - 1)};
  std::vector<float> output =
      enola::function::exponential_linear_unit(input, alpha);
  EXPECT_EQ(output.size(), expected_output.size());
  for (size_t i = 0; i < output.size(); ++i) {
    EXPECT_FLOAT_EQ(output[i], expected_output[i]);
  }
}

TEST(ELUTest, EmptyInputVector) {
  std::vector<float> input;
  float              alpha = 0.5f;

  try {
    std::vector<float> output =
        enola::function::exponential_linear_unit(input, alpha);
    FAIL()
        << "expected std::invalid_argument exception for empty input vector.";
  } catch (const std::invalid_argument &error) {
    EXPECT_STREQ("input vector cannot be empty", error.what());
  }
}

TEST(ELUTest, NegativeAlpha) {
  std::vector<float> input = {1.0f, -1.0f};
  float              alpha = -0.1f;

  try {
    std::vector<float> output =
        enola::function::exponential_linear_unit(input, alpha);
    FAIL() << "expected std::invalid_argument exception for negative alpha.";
  } catch (const std::invalid_argument &error) {
    EXPECT_STREQ("alpha must be non-negative number", error.what());
  }
}
