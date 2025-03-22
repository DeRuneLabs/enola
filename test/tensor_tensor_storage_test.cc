#include <gtest/gtest.h>

#include "../enola/tensor/tensor_storage.hpp"
#include <vector>

TEST(TensorStorageTest, SingleElementTensor) {
  std::array<std::size_t, 1> shape = {1};

  enola::tensor::Storage<int, enola::tensor::CPU> storage(shape);

  EXPECT_EQ(storage.size(), 1);
  storage[0] = 42;
  EXPECT_EQ(storage[0], 42);
}

TEST(TensorStorageTest, LargeTensor) {
  std::vector<std::size_t> shape = {1000, 1000};

  enola::tensor::Storage<int, enola::tensor::CPU> storage(shape);
  EXPECT_EQ(storage.size(), 1000 * 1000);

  storage[0]    = 1;
  storage[9999] = 2;

  EXPECT_EQ(storage[0], 1);
  EXPECT_EQ(storage[9999], 2);
}

TEST(TensorStorageTest, FixedSizeCompilationTimeEvaluation) {
  constexpr std::array<std::size_t, 3> shape = {2, 3, 4};

  constexpr std::size_t num_elements = enola::tensor::num_elements(shape);

  static_assert(num_elements == 24, "Compile-time evaluation failed");

  enola::tensor::Storage<int, enola::tensor::CPU> storage(shape);
  EXPECT_EQ(storage.size(), 24);
}

TEST(TensorStorageTest, FixedShapeInitialization) {
  std::vector<std::size_t> shape = {2, 3, 4};

  enola::tensor::Storage<double, enola::tensor::CPU> storage(shape);

  EXPECT_EQ(storage.size(), 24);

  storage[0] = 3.5;
  storage[1] = 4.5;
  EXPECT_DOUBLE_EQ(storage[0], 3.5);
  EXPECT_DOUBLE_EQ(storage[1], 4.5);
}

TEST(TensorStorageTest, DynamicShapeInitialization) {
  std::vector<std::size_t> shape = {3, 4};

  enola::tensor::Storage<double, enola::tensor::CPU> storage(shape);

  EXPECT_EQ(storage.size(), 12);

  storage[0] = 1.0;
  storage[1] = 2.0;
  for (std::size_t i = 2; i < storage.size(); ++i) {
    EXPECT_DOUBLE_EQ(storage[i], 0.0);
  }
}
