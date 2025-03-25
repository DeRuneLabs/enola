#include <gtest/gtest.h>

#include "../enola/function/activation/softplus.hpp"
#include <stdexcept>

TEST(SoftplusTest, VectorInput) {
  std::vector<double> input    = {2.3, 0.6, -2.0, -3.8};
  std::vector<double> expected = {
      2.39554546, 1.03748795, 0.12692801, 0.02212422};
  std::vector<double> result = enola::function::softplus(input);

  ASSERT_EQ(result.size(), expected.size());

  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_NEAR(result[i], expected[i], 1e-6);
  }
}

TEST(SoftplusTest, RawPointerInput) {
  float  raw_input[] = {-9.2f, -0.3f, 0.45f, -4.56f};
  size_t size        = sizeof(raw_input) / sizeof(raw_input[0]);
  float  expected[]  = {
      1.01034298e-4f, 0.554355244f, 0.943248946f, 0.0104077103f};

  auto result = enola::function::softplus(raw_input, size);

  ASSERT_EQ(result->size(), size);

  for (size_t i = 0; i < size; ++i) {
    EXPECT_NEAR((*result)[i], expected[i], 1e-6f);
  }
}

TEST(SoftplusTest, EmptyVectorInput) {
  std::vector<double> input  = {};
  std::vector<double> result = enola::function::softplus(input);

  EXPECT_TRUE(result.empty());
}

TEST(SoftplusTest, NullPointerInput) {
  double* input = nullptr;
  size_t  size  = 0;

  EXPECT_THROW(enola::function::softplus(input, size), std::invalid_argument);
}
