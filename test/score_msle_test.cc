#include <gtest/gtest.h>

#include "../enola/score/msle.hpp"

TEST(MSLETest, BasicFunction) {
  std::vector<double> y_true = {1.0, 2.0, 3.0, 4.0, 5.0};
  std::vector<double> y_pred = {0.8, 2.1, 2.9, 4.2, 5.2};

  double expected_value = 0.0030860877925181344;
  double res = enola::score::mean_squared_logarithmic_error(y_true, y_pred);
  EXPECT_NEAR(res, expected_value, 1e-9);
}

TEST(MSLETest, MismatchInput) {
  std::vector<double> y_true = {1.0, 2.0, 3.0};
  std::vector<double> y_pred = {0.8, 2.1};

  EXPECT_THROW(enola::score::mean_squared_logarithmic_error(y_true, y_pred),
               std::invalid_argument);
}

TEST(MSLETest, TensorViewMismatchedShapes) {
  std::vector<std::size_t>                           shape_true = {2, 3};
  enola::tensor::Storage<double, enola::tensor::CPU> true_storage(shape_true);

  std::vector<std::size_t>                           shape_pred = {3, 2};
  enola::tensor::Storage<double, enola::tensor::CPU> pred_storage(shape_pred);

  std::vector<std::size_t> strides_true = {3, 1};
  std::vector<std::size_t> strides_pred = {2, 1};

  enola::tensor::TensorView<double> y_true(
      true_storage, shape_true, strides_true);
  enola::tensor::TensorView<double> y_pred(
      pred_storage, shape_pred, strides_pred);

  EXPECT_THROW(enola::score::mean_squared_logarithmic_error(y_true, y_pred),
               std::invalid_argument);
}

TEST(MSLETest, NegativeValuesInYTrue) {
  std::vector<double> y_true = {1.0, -2.0, 3.0};
  std::vector<double> y_pred = {0.8, 2.1, 2.9};

  EXPECT_THROW(enola::score::mean_squared_logarithmic_error(y_true, y_pred),
               std::invalid_argument);
}

TEST(MSLETest, NegativeValuesInYPred) {
  std::vector<double> y_true = {1.0, 2.0, 3.0};
  std::vector<double> y_pred = {0.8, -2.1, 2.9};

  EXPECT_THROW(enola::score::mean_squared_logarithmic_error(y_true, y_pred),
               std::invalid_argument);
}
