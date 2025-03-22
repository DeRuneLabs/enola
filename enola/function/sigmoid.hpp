#ifndef FUNCTION_SIGMOID_HPP
#define FUNCTION_SIGMOID_HPP

#include <algorithm>
#include <cmath>
#include <vector>

namespace enola {
namespace function {
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
inline std::vector<float> sigmoid(const std::vector<float>& m1) {
  if (m1.empty()) {
    return {};  // return empty vector if the input is empty
  }

  // pre-allocate output vector with the same size as the input vector
  std::vector<float> output(m1.size());
  // apply sigmoid function to each element of the input vector
  std::transform(m1.begin(),
                 m1.end(),        // input range
                 output.begin(),  // output range
                 [](float x) {    // lambda function to compute sigmoid
                   return 1.0f /
                          (1.0f + std::exp(-x));  // return sigmoid formula
                 });
  return output;  // return the transformed vector
}
}  // namespace function
}  // namespace enola

#endif  // !FUNCTION_SIGMOID_HPP
