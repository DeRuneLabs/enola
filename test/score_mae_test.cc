#include <gtest/gtest.h>

#include "../enola/score/mae.hpp"
#include <stdexcept>

TEST(MAETest, IndenticalTensor) {
  std::vector<std::size_t>                        shape = {2, 3};
  enola::tensor::Storage<int, enola::tensor::CPU> predict(shape);
  enola::tensor::Storage<int, enola::tensor::CPU> actual(shape);

  for (std::size_t i = 0; i < predict.size(); ++i) {
    predict[i] = static_cast<int>(i + 1);
    actual[i]  = static_cast<int>(i + 1);
  }

  double score = enola::score::mae(predict, actual);
  EXPECT_DOUBLE_EQ(score, 0.0);
}

TEST(MAETest, DifferentTensors) {
  std::vector<std::size_t> shape = {2, 3};
  enola::tensor::Storage<int, enola::tensor::CPU> predict(shape);
  enola::tensor::Storage<int, enola::tensor::CPU> actual(shape);

  predict[0] = 1;
  predict[1] = 4;
  predict[2] = 3;
  predict[3] = 2;
  predict[4] = 5;
  predict[5] = 6;

  actual[0] = 1;
  actual[1] = 2;
  actual[2] = 3;
  actual[3] = 4;
  actual[4] = 5;
  actual[5] = 6;

  double score = enola::score::mae(predict, actual);
  EXPECT_NEAR(score, 0.666667, 1e-6);
}
