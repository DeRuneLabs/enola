#include <gtest/gtest.h>

#include "../enola/math/vector.hpp"
#include <cstdlib>

template <unsigned int N>
bool VectorEquals(const enola::Vector<N>& v1,
                  const enola::Vector<N>& v2,
                  double                  epsilon = 1e-6) {
  for (unsigned int i = 0; i < N; ++i) {
    if (std::abs(v1.data[i] - v2.data[i]) > epsilon) {
      return false;
    }
  }
  return true;
}

TEST(VectorTest, DefaultConstruct) {
  enola::Vector<3> v;
  EXPECT_TRUE(true);
}

TEST(VectorTest, CopyConstruct) {
  enola::Vector<2> v1 = {1.0, 2.0};
  enola::Vector<2> v2 = v1;
  v2                  = v1;

  EXPECT_TRUE(VectorEquals<2>(v1, v2));
}

TEST(VectorTest, AssignOperator) {
  enola::Vector<2> v1 = {1.0, 2.0};
  enola::Vector<2> v2;
  v2 = v1;

  EXPECT_TRUE(VectorEquals<2>(v1, v2));
}

TEST(VectorTest, Adds) {
  enola::Vector<2> v1     = {1.0, 2.0};
  enola::Vector<2> v2     = {3.0, 4.0};
  enola::Vector<2> result = v1 + v2;

  enola::Vector<2> expected = {4.0, 6.0};
  EXPECT_TRUE(VectorEquals<2>(result, expected));
}

TEST(VectorTest, Substract) {
  enola::Vector<2> v1     = {5.0, 7.0};
  enola::Vector<2> v2     = {2.0, 3.0};
  enola::Vector<2> result = v1 - v2;

  enola::Vector<2> expected = {3.0, 4.0};
  EXPECT_TRUE(VectorEquals<2>(result, expected));
}

TEST(VectorTest, ScalarMultiplication) {
  enola::Vector<2> v      = {2.0, 3.0};
  enola::Vector<2> result = v * 2.0;

  enola::Vector<2> expected = {4.0, 6.0};
  EXPECT_TRUE(VectorEquals<2>(result, expected));
}

TEST(VectorTest, ScalarDivision) {
  enola::Vector<2> v      = {6.0, 8.0};
  enola::Vector<2> result = v / 2.0;

  enola::Vector<2> expected = {3.0, 4.0};
  EXPECT_TRUE(VectorEquals<2>(result, expected));
}

TEST(VectorTest, DotProductMethod) {
  enola::Vector<3> v1 = {1.0, 2.0, 3.0};
  enola::Vector<3> v2 = {4.0, 5.0, 6.0};

  real result   = v1.dot(v2);
  real expected = 1 * 4 + 2 * 5 + 3 * 6;

  EXPECT_NEAR(result, expected, 1e-6);
}

TEST(VectorTest, DotProductOperator) {
  enola::Vector<3> v1 = {1.0, 2.0, 3.0};
  enola::Vector<3> v2 = {4.0, 5.0, 6.0};

  real result   = v1 * v2;
  real expected = 32.0;

  EXPECT_NEAR(result, expected, 1e-6);
}
