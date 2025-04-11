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

TEST(TensorStorageTest, BoundCheck) {
#define DEBUG
  std::vector<std::size_t>                        shape = {2, 3};
  enola::tensor::Storage<int, enola::tensor::CPU> storage(shape);

  EXPECT_NO_THROW(storage[0]);
#undef DEBUG
}

TEST(TensorStorageTest, ResizeStorage) {
  std::vector<std::size_t>                        initial_shape = {2, 3};
  enola::tensor::Storage<int, enola::tensor::CPU> storage(initial_shape);

  EXPECT_EQ(storage.size(), 6);

  std::vector<std::size_t> new_shape = {3, 4};
  storage.resize(new_shape);

  EXPECT_EQ(storage.size(), 12);
  for (std::size_t i = 0; i < storage.size(); ++i) {
    EXPECT_EQ(storage[i], 0);
  }

  std::vector<std::size_t> invalid_shape = {0, 4};
  EXPECT_THROW(storage.resize(invalid_shape), std::invalid_argument);
}

TEST(StorageTestGPU, VectorShape) {
#ifdef GPU_SUPPORT_AVAILABLE
  std::vector<std::size_t>                          shape = {2, 3};
  enola::tensor::Storage<float, enola::tensor::GPU> storage(shape);

  EXPECT_EQ(storage.size(), 6);
  EXPECT_EQ(storage.shape(), shape);
#else
  GTEST_SKIP() << "gpu not support opencl";
#endif
}
