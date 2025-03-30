#include <gtest/gtest.h>

#include "../enola/tensor/ops.hpp"

TEST(TensorOpsTest, ElementWiseAdd) {
  std::vector<std::size_t>                        shape = {2, 3};
  enola::tensor::Storage<int, enola::tensor::CPU> lhs(shape);
  enola::tensor::Storage<int, enola::tensor::CPU> rhs(shape);

  for (std::size_t i = 0; i < lhs.size(); ++i) {
    lhs[i] = static_cast<int>(i);
    rhs[i] = static_cast<int>(i * 2);
  }

  auto result = enola::tensor::add(lhs, rhs);
  EXPECT_EQ(result.size(), lhs.size());
}

TEST(TensorOpsTest, ElementWiseSub) {
  std::vector<std::size_t> shape = {2, 3};
  enola::tensor::Storage<int, enola::tensor::CPU> lhs(shape);
  enola::tensor::Storage<int, enola::tensor::CPU> rhs(shape);

  for (std::size_t i = 0; i < lhs.size(); ++i) {
    lhs[i] = static_cast<int>(i);
    rhs[i] = static_cast<int>(i * 2);
  }

  auto result = enola::tensor::subtract(lhs, rhs);
  EXPECT_EQ(result.size(), lhs.size());
}

TEST(TensorOpsTest, ElementWiseMulti) {
  std::vector<std::size_t> shape = {2, 3};
  enola::tensor::Storage<int, enola::tensor::CPU> lhs(shape);
  enola::tensor::Storage<int, enola::tensor::CPU> rhs(shape);

  for (std::size_t i = 0; i < lhs.size(); ++i) {
    lhs[i] = static_cast<int>(i);
    rhs[i] = static_cast<int>(i * 2);
  }

  auto result = enola::tensor::multiply(lhs, rhs);
  EXPECT_EQ(result.size(), lhs.size());

  for (std::size_t i = 0; i < result.size(); ++i) {
    EXPECT_EQ(result[i], lhs[i] * rhs[i]);
  }
}

TEST(TensorOpsTest, ElementWiseDivision) {
  std::vector<std::size_t> shape = {2, 3};
  enola::tensor::Storage<int, enola::tensor::CPU> lhs(shape);
  enola::tensor::Storage<int, enola::tensor::CPU> rhs(shape);

  for (std::size_t i = 0; i < lhs.size(); ++i) {
    lhs[i] = static_cast<int>(i + 1);
    rhs[i] = static_cast<int>(i + 1);
  }

  auto result = enola::tensor::divide(lhs, rhs);
  EXPECT_EQ(result.size(), lhs.size());

  for (std::size_t i = 0; i < result.size(); ++i) {
    EXPECT_EQ(result[i], lhs[i] / rhs[i]);
  }
}

TEST(TensorOpsTest, SumMean) {
  std::vector<std::size_t> shape = {2, 3};
  enola::tensor::Storage<int, enola::tensor::CPU> tensor(shape);

  for (std::size_t i = 0; i < tensor.size(); ++i) {
    tensor[i] = static_cast<int>(i + 1);
  }

  EXPECT_EQ(enola::tensor::sum(tensor), 21);
}
