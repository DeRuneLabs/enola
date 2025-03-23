#ifndef FUNCTION_ACTIVATION_RELU_HPP
#define FUNCTION_ACTIVATION_RELU_HPP

#include <algorithm>
#include <type_traits>
#include <vector>

namespace enola {
namespace function {

/**
 * @brief appplied rectified linear unit (RELU) activation function element-wise
 *
 * formula
 * \[
 * f(x) =
 * \begin{cases}
 *       0 & \text{if } x < 0. \\
 *       x & \test{if } x \geq 0
 * /end{cases}
 * ]
 *
 * @tparam T numeric type
 * @param z constant reference to vector of type T representing the input values
 *          each element of the vector is treated as an independent input to the
 * relu
 *
 * @return vector of type T containing the RELU-transformed values of the input
 * vector
 *         - input vector is empty, an empty vector was return
 *         - otherwise, the output vector has the same size as the input vector,
 * with each element being the result of applying the ReLU function to the
 * corresponding input element
 *
 */
template <typename T>
inline std::vector<T> relu(const std::vector<T>& z) {
  // make sure type T numeric type
  static_assert(std::is_arithmetic_v<T>, "relu only support numeric types");

  // return empty vector if the input was empty
  if (z.empty()) {
    return {};
  }

  // pre-allocate the output vector with the same size as the input vector
  std::vector<T> output(z.size());

  // apply the ReLU function to each element of the input vector
  std::transform(z.begin(),
                 z.end(),         // input range
                 output.begin(),  // output range
                 [](T x) -> T {   // lambda function to perform ReLU
                   return (x < T(0)) ? T(0) : x;
                 });
  // return transformed vector
  return output;
}

/**
 * @brief applies the derivative of rectified linear unit activation function
 *
 * formula
 * \[
 * f'(x) =
 * \begin{cases}
 *   0 & \text{if } x < 0 \\
 *   1 & \text{if } x \geq 0
 * \end{cases}
 * ]
 *
 * @tparam T numeric type
 * @param z constant reference ot a vector of type T representing the input
 * values each element of the vector is treated as an independent input to the
 * ReLU
 *
 * @return vector of type T containing the ReLU derivative-transformed value of
 * the input vector
 *     - if the input vector is empty, an empty vector is returned
 *     - otherwise, the output vector has the same size as the input vector
 *       with each element being the result of applying the ReLU derivative
 * function to the corresponding input element
 */
template <typename T>
inline std::vector<T> relu_derivative(const std::vector<T>& z) {
  // ensure T is numeric
  static_assert(std::is_arithmetic_v<T>,
                "relu derivative only support numeric types");

  // return an empty vector if the input is empty
  if (z.empty()) {
    return {};
  }

  // pre-allocate the output vector with the same size as the input vector
  std::vector<T> output(z.size());

  // apply the ReLU derivative function to each element of the input vector
  std::transform(z.begin(),  // input range
                 z.end(),    // input range
                 output.begin(),
                 [](T x) -> T { return (x < T(0)) ? T(0) : T(1); });

  return output;
}

}  // namespace function
}  // namespace enola

#endif  // !FUNCTION_ACTIVATION_RELU_HPP
