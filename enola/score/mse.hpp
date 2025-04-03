#ifndef FUNCTION_SCORE_MSE_HPP
#define FUNCTION_SCORE_MSE_HPP

#include "../tensor/tensor_storage.hpp"
#include <stdexcept>
#include <type_traits>

namespace enola {
namespace score {

/**
 * @brief Compute the Mean Squared Error (MSE) between predicted and actual
 * tensors.
 *
 * The MSE measures the average squared difference between the predicted and
 * actual values. It is defined as:
 * \[
 *   \text{MSE} = \frac{1}{n} \sum_{i=1}^{n} (\text{predict}[i] -
 * \text{actual}[i])^2
 * \]
 *
 * @tparam T The type of elements stored in the tensors (must be numeric).
 * @param predict A tensor containing predicted values.
 * @param actual A tensor containing actual (ground truth) values.
 * @return The computed MSE score as a double.
 *
 * @throws std::invalid_argument If the input tensors are empty or of different
 * sizes.
 */
template <typename T>
[[nodiscard]] double mse(
    const enola::tensor::Storage<T, enola::tensor::CPU>& predict,
    const enola::tensor::Storage<T, enola::tensor::CPU>& actual) {
  // make sure input are numeric type
  static_assert(std::is_arithmetic_v<T>, "tensor element must be numeric");

  // validating input size
  if (predict.size() == 0 || actual.size() == 0) {
    throw std::invalid_argument("input tensor mut not be empty");
  }

  if (predict.size() != actual.size()) {
    throw std::invalid_argument("input tensor must have the same size");
  }

  double sum_square_difference = 0.0;
  for (std::size_t i = 0; i < predict.size(); ++i) {
    double diff =
        static_cast<double>(predict[i]) - static_cast<double>(actual[i]);
    sum_square_difference += diff * diff; // square the difference
  }

  // return the mean
  return sum_square_difference / predict.size();
}

}  // namespace score
}  // namespace enola

#endif  // !FUNCTION_SCORE_MSE_HPP
