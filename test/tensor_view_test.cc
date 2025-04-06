#include <gtest/gtest.h>

#include "../enola/tensor/view.hpp"
#include <cstddef>

TEST(TensorViewTest, Access) {
  std::vector<std::size_t>                           shape = {2, 3};
  enola::tensor::Storage<double, enola::tensor::CPU> storage(shape);

  storage[0] = 1.0;
  storage[1] = 2.0;
  storage[2] = 3.0;
  storage[3] = 4.0;
  storage[4] = 5.0;
  storage[5] = 6.0;

  std::vector<std::size_t> view_shape = {2, 3};
  std::vector<std::size_t> strides    = {3, 1};

  enola::tensor::TensorView<double> view(storage, view_shape, strides);

  EXPECT_DOUBLE_EQ(view({0, 0}), 1.0);
  EXPECT_DOUBLE_EQ(view({0, 1}), 2.0);
  EXPECT_DOUBLE_EQ(view({0, 2}), 3.0);
  EXPECT_DOUBLE_EQ(view({1, 0}), 4.0);
  EXPECT_DOUBLE_EQ(view({1, 1}), 5.0);
  EXPECT_DOUBLE_EQ(view({1, 2}), 6.0);

  view({1, 1}) = 99.0;
  EXPECT_DOUBLE_EQ(storage[4], 99.0);
}

TEST(TensorViewTest, InvalidIndc) {
  std::vector<std::size_t>                           shape = {2, 3};
  enola::tensor::Storage<double, enola::tensor::CPU> storage(shape);

  std::vector<std::size_t> view_shape = {2, 3};
  std::vector<std::size_t> strides    = {3, 1};

  enola::tensor::TensorView<double> view(storage, view_shape, strides);

  std::vector<std::size_t> invalid_indcs = {2, 0};
  EXPECT_THROW(view(invalid_indcs), std::out_of_range);
}

TEST(TensorViewTest, ExceedsBounds) {
  std::vector<std::size_t>                           shape = {2, 3};
  enola::tensor::Storage<double, enola::tensor::CPU> storage(shape);

  std::vector<std::size_t> view_shape = {3, 3};
  std::vector<std::size_t> strides    = {3, 1};

  EXPECT_THROW(enola::tensor::TensorView<double>(storage, view_shape, strides),
               std::out_of_range);
}
