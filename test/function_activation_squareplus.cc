#include <gtest/gtest.h>

#include "../enola/function/activation/squareplus.hpp"

TEST(SquarePlusTest, RawPointerInput) {
  float  raw_input[] = {-9.2f, -0.3f, 0.45f, -4.56f};
  size_t size        = sizeof(raw_input) / sizeof(raw_input[0]);
  float  beta        = 3.0f;
  float  expected[]  = {0.0808119f, 0.72891979f, 1.11977651f, 0.15893419f};

  auto result = enola::function::squareplus(raw_input, size, beta);

  ASSERT_EQ(result->size(), size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_NEAR((*result)[i], expected[i], 1e-6f);
  }
}

TEST(SquarePlusTest, VectorInput) {
  std::vector<double> input    = {2.3, 0.6, -2.0, -3.8};
  double              beta     = 2.0;
  std::vector<double> expected = {2.5, 1.06811457, 0.22474487, 0.12731349};
  std::vector<double> result   = enola::function::squareplus(input, beta);

  ASSERT_EQ(result.size(), expected.size());
  for (size_t i = 0; i < result.size(); ++i) {
    EXPECT_NEAR(result[i], expected[i], 1e-6);
  }
}

TEST(SquarePlusTest, NullPointerInput) {
  double *input = nullptr;
  size_t  size  = 0;
  double  beta  = 2.0;

  EXPECT_THROW(enola::function::squareplus(input, size, beta),
               std::invalid_argument);
}
