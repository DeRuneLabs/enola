#include <gtest/gtest.h>

#include "../enola/math/exp.hpp"
#include <cmath>

TEST(ExpTest, ZeroInput) {
  double res = enola::math::exp(0.0);
  EXPECT_DOUBLE_EQ(res, 1.0);
}

TEST(ExpTest, SmallPositive) {
  double input = 1.0, expected = std::exp(input),
         result = enola::math::exp(input);
  EXPECT_NEAR(result, expected, 1e-6);
}

TEST(ExpTest, PrecisionNearZero) {
  double input = 1e-6, expected = std::exp(input),
         result = enola::math::exp(input);
  EXPECT_NEAR(result, expected, 1e-6);
}

TEST(ExpTest, ConvergenceSpeed) {
  double input = 5.0, expected = std::exp(input),
         result = enola::math::exp(input);
  EXPECT_NEAR(result, expected, 1e-6);
}
