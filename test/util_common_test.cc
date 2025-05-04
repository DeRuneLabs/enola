#include <gtest/gtest.h>

#include "../enola/utils/common.hpp"

constexpr real EPSILON = 1e-5f;

TEST(common, SqrtFunction) {
  EXPECT_NEAR(enola::sqrt(4.0f), 2.0f, EPSILON);
  EXPECT_NEAR(enola::sqrt(2.0f), ::sqrtf(2.0f), EPSILON);
  EXPECT_NEAR(enola::sqrt(0.0f), 0.0f, EPSILON);
}

TEST(common, SinFunction) {
  EXPECT_NEAR(enola::sin(0.0f), ::sinf(0.0f), EPSILON);
  EXPECT_NEAR(enola::sin(M_PI / 2), ::sinf(M_PI / 2), EPSILON);
  EXPECT_NEAR(enola::sin(M_PI), ::sinf(M_PI), EPSILON);
}

TEST(common, TanFunction) {
  EXPECT_NEAR(enola::tan(0.0f), ::tanf(0.0f), EPSILON);
  EXPECT_NEAR(enola::tan(M_PI / 4), ::tanf(M_PI / 4), EPSILON);
}

TEST(common, CotFunction) {
  EXPECT_NEAR(enola::cot(M_PI / 4), 1.0f, EPSILON);
  EXPECT_NEAR(enola::cot(M_PI / 6), 1.0f / ::tanf(M_PI / 6), EPSILON);
}

TEST(common, ClampFunction) {
  EXPECT_EQ(enola::clamp(3.0f, 1.0f, 5.0f), 3.0f);
  EXPECT_EQ(enola::clamp(0.0f, 1.0f, 5.0f), 1.0f);
  EXPECT_EQ(enola::clamp(6.0f, 1.0f, 5.0f), 5.0f);
}

TEST(common, MaxFunction) {
  EXPECT_EQ(enola::max(3.0f, 5.0f), 5.0f);
  EXPECT_EQ(enola::max(7.0f, 2.0f), 7.0f);
  EXPECT_EQ(enola::max(-1.0f, -1.0f), -1.0f);
}

TEST(common, MinFunction) {
  EXPECT_EQ(enola::min(3.0f, 5.0f), 3.0f);
  EXPECT_EQ(enola::min(7.0f, 2.0f), 2.0f);
  EXPECT_EQ(enola::min(-1.0f, -1.0f), -1.0f);
}

TEST(common, RadianConversion) {
  EXPECT_NEAR(enola::radians(180.0f), M_PI, EPSILON);
  EXPECT_NEAR(enola::radians(90.0f), M_PI / 2, EPSILON);
  EXPECT_NEAR(enola::radians(0.0f), 0.0f, EPSILON);
}

