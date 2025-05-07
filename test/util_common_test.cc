#include <gtest/gtest.h>

#include "../enola/utils/common.hpp"
#include <cmath>

constexpr real EPSILON = std::numeric_limits<real>::epsilon() * 10;

TEST(MathUtils, SquareTest) {
  EXPECT_NEAR(enola::square(2.0), 4.0, EPSILON);
  EXPECT_NEAR(enola::square(1.5), 2.25, EPSILON);
  EXPECT_NEAR(enola::square(0.0), 0.0, EPSILON);
}

TEST(MathUtils, CubeTest) {
  EXPECT_NEAR(enola::cube(2.0), 8.0, EPSILON);
  EXPECT_NEAR(enola::cube(1.5), 3.375, EPSILON);
}

TEST(MathUtils, CosNearZero) {
  real angle = 1e-6;
  EXPECT_NEAR(enola::cos(angle), std::cos(angle), EPSILON);
}

TEST(MathUtils, CosNearPi) {
  real angle = M_PI / 2 - 1e-6;
  EXPECT_NEAR(enola::cos(angle), std::cos(angle), EPSILON);
}
