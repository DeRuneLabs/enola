#include "../enola/matrix/tensor.hpp"

#include <gtest/gtest.h>

#include <cstdint>
#include <stdexcept>

TEST(TensorTest, InitializeAndDimension) {
  int64_t dim1 = 2, dim2 = 3, dim3 = 4;
  tensor  t(dim1, dim2, dim3);

  auto [d1, d2, d3] = t.get_dimension();
  EXPECT_EQ(d1, dim1);
  EXPECT_EQ(d2, dim2);
  EXPECT_EQ(d3, dim3);
}

TEST(TensorTest, AccessModifyElement) {
  int64_t dim1 = 2, dim2 = 3, dim3 = 4;
  tensor  t(dim1, dim2, dim3);

  t(0, 0, 0) = 42;
  t(1, 2, 3) = 99;

  EXPECT_EQ(t(0, 0, 0), 42);
  EXPECT_EQ(t(1, 2, 3), 99);

  EXPECT_EQ(t(0, 1, 2), 0);
  EXPECT_EQ(t(1, 0, 0), 0);
}

TEST(TensorTest, OutOfBounds) {
  int64_t dim1 = 2, dim2 = 3, dim3 = 4;
  tensor  t(dim1, dim2, dim3);

  EXPECT_NO_THROW(t(1, 2, 3));

  EXPECT_THROW(t(2, 0, 0), std::out_of_range);
  EXPECT_THROW(t(0, 3, 0), std::out_of_range);
  EXPECT_THROW(t(0, 0, 4), std::out_of_range);
}

TEST(TensorTest, LargeTensor) {
  int64_t dim1 = 100, dim2 = 100, dim3 = 100;
  tensor  t(dim1, dim2, dim3);

  auto [d1, d2, d3] = t.get_dimension();
  EXPECT_EQ(d1, dim1);
  EXPECT_EQ(d2, dim2);
  EXPECT_EQ(d3, dim3);

  EXPECT_EQ(t(50, 50, 50), 0);
}

TEST(TensorTest, DefaultInitialization) {
  int64_t dim1 = 3, dim2 = 3, dim3 = 3;
  tensor  t(dim1, dim2, dim3);

  for (int64_t i = 0; i < dim1; ++i) {
    for (int64_t j = 0; j < dim2; ++j) {
      for (int64_t k = 0; k < dim3; ++k) {
        EXPECT_EQ(t(i, j, k), 0);
      }
    }
  }
}
