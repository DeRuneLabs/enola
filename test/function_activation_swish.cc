#include <gtest/gtest.h>

#include "../enola/function/activation/swish.hpp"

TEST(SwishTest, HandleEmptyInput) {
  std::vector<float> input  = {};
  float              beta   = 1.0f;
  std::vector<float> result = enola::function::swish(input, beta);

  EXPECT_TRUE(result.empty());
}

TEST(SwishTest, SingleElementVector) {
  std::vector<float> input  = {-2.0f};
  float              beta   = 1.0f;
  std::vector<float> result = enola::function::swish(input, beta);

  EXPECT_NEAR(result[0], -0.23840584f, 1e-6);
}

TEST(SwishTest, MultiElementBeta1) {
  std::vector<float> input  = {-1.0f, 1.0f, 2.0f};
  float              beta   = 1.0f;
  std::vector<float> result = enola::function::swish(input, beta);

  EXPECT_NEAR(result[0], -0.26894142f, 1e-6);
  EXPECT_NEAR(result[1], 0.73105858f, 1e-6);
  EXPECT_NEAR(result[2], 1.76159416f, 1e-6);
}

TEST(SwishTest, LargeInput) {
  std::vector<float> input  = {-100.0f, 100.0f};
  float              beta   = 1.0f;
  std::vector<float> result = enola::function::swish(input, beta);
  EXPECT_NEAR(result[0], 0.0f, 1e-6);
  EXPECT_NEAR(result[1], 100.0f, 1e-6);
}

TEST(SwishTest, ZeroInput) {
  std::vector<float> input  = {0.0f};
  float              beta   = 1.0f;
  std::vector<float> result = enola::function::swish(input, beta);
  EXPECT_NEAR(result[0], 0.0f, 1e-6);
}
