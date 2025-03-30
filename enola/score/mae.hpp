#ifndef FUNCTION_SCORE_MAE_HPP
#define FUNCTION_SCORE_MAE_HPP

#include "../tensor/tensor_storage.hpp"
#include <cstdlib>
#include <stdexcept>
#include <type_traits>

namespace enola {
namespace score {

/**
 * @brief compute the mean absolute error (mae) between predict and actual
 * tensor
 *
 * the mae measure the avreange absolute difference between the predicted and
 * actual
 *
 * formual defined as
 * \[
 *   \text{MAE} = \frac{1}{n} \sum_{i=1}^{n} | \text{predict}[i] -
 * \text{actual}[i] |
 * \]
 *
 * @tparam T type element stored in tensor (must numeric)
 * @param predict tensor containing predicted values
 * @return computed mae score as double
 *
 * @throws std::invalid_argument if the input tensor are empyt
 */
template <typename T>
[[nodiscard]] double mae(
    const enola::tensor::Storage<T, enola::tensor::CPU>& predict,
    const enola::tensor::Storage<T, enola::tensor::CPU>& actual) {
  // make sure input are numeric type
  static_assert(std::is_arithmetic_v<T>, "tensor element must be numeric");

  // validate input size
  if (predict.size() == 0 || actual.size() == 0) {
    throw std::invalid_argument("input tensor must be not empty");
  }
  if (predict.size() != actual.size()) {
    throw std::invalid_argument("input tensor must have same size");
  }

  // calculate the absolute diffrence
  double sum_difference = 0.0;
  for (std::size_t i = 0; i < predict.size(); ++i) {
    sum_difference += std::abs(static_cast<double>(predict[i]) -
                               static_cast<double>(actual[i]));
  }
  // return the mean
  return sum_difference / predict.size();
}

}  // namespace score
}  // namespace enola

#endif  // !FUNCTION_SCORE_MAE_HPP
