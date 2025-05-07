#include <gtest/gtest.h>

#include "../enola/math/vector_buff.hpp"

constexpr real EPSILON = std::numeric_limits<real>::epsilon() * 10;

TEST(VectorBuffTest, ProductSumTwo) {
  enola::vector_buff X = {1.0, 2.0, 3.0};
  enola::vector_buff Y = {4.0, 5.0, 6.0};

  EXPECT_NEAR(enola::product_sum(X, Y), 1 * 4 + 2 * 5 + 3 * 6, EPSILON);
}

TEST(VectorBuffTest, QuotientSum) {
  enola::vector_buff X = {2.0, 4.0, 6.0};
  enola::vector_buff Y = {1.0, 2.0, 3.0};

  real expected = 2 / 1 + 4 / 2 + 6 / 3;
  EXPECT_NEAR(enola::quotient_sum(X, Y), expected, EPSILON);
}

TEST(VectorBuffTest, SumSquare) {
  enola::vector_buff X        = {1.0, 2.0, 3.0};
  real               expected = 1 * 1 + 2 * 2 + 3 * 3;
  EXPECT_NEAR(enola::sum_square(X), expected, EPSILON);
}
