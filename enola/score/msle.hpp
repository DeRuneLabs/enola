#ifndef SCORE_MSLE_HPP
#define SCORE_MSLE_HPP

#include "../tensor/view.hpp"
#include <cmath>
#include <stdexcept>

namespace enola {
namespace score {

/**
 * @brief calculate the mean squared logarithmic error
 *
 * mean suqare logarithmic error measeure the squared logarithmic difference
 * between true values
 * (\( y_{\text{true}} \)) and predicted values (\( y_{\text{pred}} \)), its is
 * particularly useful for regression problems where relative differences are
 * more important than absolute difference, MSLE penalize underestimate more
 * heavily than overestimate
 *
 * formula of MSLE
 * \[
 * \text{MSLE} = \frac{1}{n} \sum_{i=1}^n \left( \log(1 + y_{\text{true}, i}) -
 * \log(1 + y_{\text{pred}, i}) \right)^2
 * \]
 *
 * @tparam Container type of the input cntainer
 * @param y_true true values (ground truth)
 * @param y_pred predicted values
 * @return mean squared logarithmic error as double
 *
 * @throws std::invalid_argument if the input have different size or containing
 * negative
 */
template <typename Container>
double mean_squared_logarithmic_error(const Container& y_true,
                                      const Container& y_pred) {
  // validate that the input have the same size
  if (y_true.size() != y_pred.size()) {
    throw std::invalid_argument("input array must have the same length");
  }

  // validate the all elements in y_true are non-negative
  for (const auto& value : y_true) {
    if (value < 0) {
      throw std::invalid_argument("true values must be non-negative");
    }
  }
  // validate that all element y_pred are non-negative
  for (const auto& value : y_pred) {
    if (value < 0) {
      throw std::invalid_argument("predicted value must be non-negative");
    }
  }

  // calculate sum of squared logarithmic error
  double sum_squared_errors = 0.0;
  for (std::size_t i = 0; i < y_true.size(); ++i) {
    // compute the logarithmic difference for the current element
    double log_diff = std::log1p(y_true[i]) - std::log1p(y_pred[i]);
    // add the squared logarithmic difference to the running sum
    sum_squared_errors += log_diff * log_diff;
  }
  // return mean squared logarithmic error
  return sum_squared_errors / static_cast<double>(y_true.size());
}

/**
 * @brief specialization of MSLE for TensorView
 *
 * this function calculate the mean squared logarithmic error (MSLE) for tensors
 * represented by TensorView object, support multi-dimensional tensors and make
 * sure compatibility with the underlying storage
 *
 * @tparam T type elements in the tensor
 * @param y_true true values (ground truth) as TensorView
 * @param y_pred predicted values as a TensorView
 * @return mean squared logarithmic error as double
 *
 * @throws std::invalid_argument if the input have different shape or containing
 * negative
 */
template <typename T>
double mean_squared_logarithmic_error(
    const enola::tensor::TensorView<T>& y_true,
    const enola::tensor::TensorView<T>& y_pred) {
  // validate that input have the same shape
  if (y_true.shape() != y_pred.shape()) {
    throw std::invalid_argument("input tensor must have the same shape");
  }

  // calculate the total number of element from tensor shape
  std::size_t total_elements = 1;
  for (const auto& dim : y_true.shape()) {
    total_elements *= dim;
  }

  // compute the sum of square logarithmic error
  double sum_squared_errors = 0.0;
  for (std::size_t i = 0; i < total_elements; ++i) {
    // convert float index `i` into multi-dimensional indices
    std::vector<std::size_t> indices(y_true.shape().size(), 0);
    std::size_t              index = i;
    for (std::size_t j = 0; j < y_true.shape().size(); ++j) {
      indices[j] = index % y_true.shape()[j];
      index /= y_true.shape()[j];
    }

    // access the true predicted values using the multi-dimensional indices
    T true_value = y_true(indices);
    T pred_value = y_pred(indices);

    // validate that both values are non-negative
    if (true_value < 0 || pred_value < 0) {
      throw std::invalid_argument(
          "all value in the tensor must be non-negative");
    }

    // calculate logarithmic difference for the current element
    double log_diff = std::log1p(true_value) - std::log1p(pred_value);
    sum_squared_errors += log_diff * log_diff;
  }

  // add squared logarithmic difference to the running sum
  return sum_squared_errors / static_cast<double>(total_elements);
}

}  // namespace score
}  // namespace enola

#endif  // !SCORE_MSLE_HPP
