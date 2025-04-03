#ifndef FUNCTION_SIGMOID_HPP
#define FUNCTION_SIGMOID_HPP

#include "../math/exp.hpp"
#include <algorithm>
#include <cmath>
#include <type_traits>
#include <vector>

namespace enola {
namespace function {

/**
 * @brief applie the sigmoid activation function to scalar value
 *
 * function formula:
 * \[
 * f(x) = \frac{1}{1 + e^{-x}}
 * \]
 *
 * @tparam T floating point type
 * @param xinput scalar value
 * @return sigmoid-transform value of the input
 */
template <typename T>
[[nodiscard]] inline T sigmoid(T x) {
  static_assert(std::is_floating_point_v<T>,
                "sigmoid only support floating-point types");

  if (x > T(100)) {
    return T(1.0);
  }
  if (x < T(-100)) {
    return T(0.0);
  }

  return T(1.0) / (T(1.0) + enola::math::exp(-x));
}

/**
 * @brief applies the sigmoid activation function element-wise to vector
 *
 * function defined as
 * \[
 * f(x) = \frac{1}{1 + e^{-x}}
 * ]
 *
 * map any real-valued input \( x \) to the range (0, 1), this function is
 * commonly used in machine learning for binary classification problems and as
 * an activation function in neural networks
 *
 * @param m1 constant reference to vector of float representing the input value,
 * each element of the vector is treated as an independent input to the sigmoid
 * function
 * @return vector of floats containing the sigmoid-transformed values of the
 * input vector
 *          - if the input vector is empty, an empty vector is returned
 *          - otherwise, output vector has the same size as the input vector,
 * with each element being the result of applying the sigmoid function to the
 * corresponding input element
 */
template <typename T>
inline std::vector<T> sigmoid(const std::vector<T>& m1) {
  // make sure tha type param floating point numbers
  static_assert(std::is_floating_point_v<T>,
                "sigmid only support floating point numbers");
  if (m1.empty()) {
    return {};  // return empty vector if the input is empty
  }

  // pre-allocate output vector with the same size as the input vector
  std::vector<T> output(m1.size());

  std::transform(m1.begin(), m1.end(), output.begin(), [](T x) -> T {
    return sigmoid(x);
  });
  return output;
}
}  // namespace function
}  // namespace enola

#endif  // !FUNCTION_SIGMOID_HPP
