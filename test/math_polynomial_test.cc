#include <gtest/gtest.h>

#include "../enola/math/polynomial.hpp"

bool polynomial_eq(const enola::Polynomial& p1, const enola::Polynomial& p2) {
  if (p1.size() != p2.size()) {
    return false;
  }
  for (size_t i = 0; i < p1.size(); ++i) {
    if (p1.get(i) != p2.get(i)) {
      return false;
    }
  }
  return true;
}

TEST(PolynomialTesting, DefaultConstruct) {
  enola::Polynomial p;
  EXPECT_EQ(p.size(), 0);
  EXPECT_EQ(p.find_order(), 0);
}

TEST(PolynomialTesting, VectorBuffConstruct) {
  enola::vector_buff v = {1.0, 2.0, 3.0};
  enola::Polynomial  p(v);
  EXPECT_EQ(p.size(), 3);
  EXPECT_EQ(p.get(0), 1.0);
  EXPECT_EQ(p.get(1), 2.0);
  EXPECT_EQ(p.get(2), 3.0);
  EXPECT_EQ(p.find_order(), 2);
}

TEST(PolynomialTesting, InitializerListConstruct) {
  enola::Polynomial p({1.0, 2.0, 3.0});
  EXPECT_EQ(p.size(), 3);
  EXPECT_EQ(p.get(0), 1.0);
  EXPECT_EQ(p.get(1), 2.0);
  EXPECT_EQ(p.get(2), 3.0);
  EXPECT_EQ(p.find_order(), 2);
}

TEST(PolynomialTesting, EvalTest) {
  enola::Polynomial p({1.0, 2.0, 3.0});
  EXPECT_DOUBLE_EQ(p.eval(0), 1.0);
  EXPECT_DOUBLE_EQ(p.eval(1), 6.0);
  EXPECT_DOUBLE_EQ(p.eval(2), 17.0);
}

TEST(PolynomialTesting, FindOrderTest) {
  enola::Polynomial p1({0.0, 0.0, 0.0});
  EXPECT_EQ(p1.find_order(), 0);

  enola::Polynomial p2({0.0, 5.0, 0.0});
  EXPECT_EQ(p2.find_order(), 1);

  enola::Polynomial p3({1.0, 2.0, 3.0});
  EXPECT_EQ(p3.find_order(), 2);
}

TEST(PolynomialTesting, addAssignTesting) {
  enola::Polynomial p1({1.0, 2.0, 3.0});
  enola::Polynomial p2({4.0, 5.0});
  p1 += p2;
  enola::Polynomial expected({5.0, 7.0, 3.0});
  EXPECT_TRUE(polynomial_eq(p1, expected));
}

TEST(PolynomialTesting, MultiplyTest) {
  enola::Polynomial p1({1.0, 2.0});
  enola::Polynomial p2({3.0, 4.0});
  enola::Polynomial result = p1 * p2;

  enola::Polynomial expected({3.0, 10.0, 8.0});
  EXPECT_TRUE(polynomial_eq(result, expected));
}

TEST(PolynomialTesting, MultiplyAssignTest) {
  enola::Polynomial p1({1.0, 2.0});
  enola::Polynomial p2({3.0, 4.0});
  p1 *= p2;
  enola::Polynomial expected({3.0, 10.0, 8.0});
  EXPECT_TRUE(polynomial_eq(p1, expected));
}

TEST(PolynomialTesting, SubtractAssignTest) {
  enola::Polynomial p1({5.0, 6.0, 7.0});
  enola::Polynomial p2({1.0, 2.0, 3.0});
  p1 -= p2;

  enola::Polynomial expected({4.0, 4.0, 4.0});
  EXPECT_TRUE(polynomial_eq(p1, expected));
}
