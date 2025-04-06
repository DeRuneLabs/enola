#ifndef SCORE_MSLE_HPP
#define SCORE_MSLE_HPP

#include "../tensor/view.hpp"
#include <cmath>
#include <stdexcept>

namespace enola {
namespace score {

template <typename Container>
double mean_squared_logarithmic_error(const Container& y_true,
                                      const Container& y_pred) {
  if (y_true.size() != y_pred.size()) {
    throw std::invalid_argument("input array must have the same length");
  }

  for (const auto& value : y_true) {
    if (value < 0) {
      throw std::invalid_argument("true values must be non-negative");
    }
  }
  for (const auto& value : y_pred) {
    if (value < 0) {
      throw std::invalid_argument("predicted value must be non-negative");
    }
  }

  double sum_squared_errors = 0.0;
  for (std::size_t i = 0; i < y_true.size(); ++i) {
    double log_diff = std::log1p(y_true[i]) - std::log1p(y_pred[i]);
    sum_squared_errors += log_diff * log_diff;
  }
  return sum_squared_errors / static_cast<double>(y_true.size());
}

template <typename T>
double mean_squared_logarithmic_error(
    const enola::tensor::TensorView<T>& y_true,
    const enola::tensor::TensorView<T>& y_pred) {
  if (y_true.shape() != y_pred.shape()) {
    throw std::invalid_argument("input tensor must have the same shape");
  }

  std::size_t total_elements = 1;
  for (const auto& dim : y_true.shape()) {
    total_elements *= dim;
  }

  double sum_squared_errors = 0.0;
  for (std::size_t i = 0; i < total_elements; ++i) {
    std::vector<std::size_t> indices(y_true.shape().size(), 0);
    std::size_t              index = i;
    for (std::size_t j = 0; j < y_true.shape().size(); ++j) {
      indices[j] = index % y_true.shape()[j];
      index /= y_true.shape()[j];
    }
    T true_value = y_true(indices);
    T pred_value = y_pred(indices);

    if (true_value < 0 || pred_value < 0) {
      throw std::invalid_argument(
          "all value in the tensor must be non-negative");
    }

    double log_diff = std::log1p(true_value) - std::log1p(pred_value);
    sum_squared_errors += log_diff * log_diff;
  }

  return sum_squared_errors / static_cast<double>(total_elements);
}

}  // namespace score
}  // namespace enola

#endif  // !SCORE_MSLE_HPP
