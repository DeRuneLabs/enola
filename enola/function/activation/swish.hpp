#ifndef FUNCTION_ACTIVATION_SWISH_HPP
#define FUNCTION_ACTIVATION_SWISH_HPP

#include "../sigmoid.hpp"
#include <algorithm>
#include <type_traits>
#include <vector>

namespace enola {
namespace function {

/**
 * @brief applies the swish activation function element-wise to a vector
 *
 * formula swish activation function
 * \[
 * f(x, \beta) = x \cdot \sigma(\beta \cdot x)
 * \]
 * where (\sigma \) is sigmoid function from ../sigmoid.hpp
 *
 * this function maps any real-valued input \(x \) to transform output,
 * controlled by the trainable parameter \( \beta \), swish is a smooth,
 *
 * @tparam T floating point type
 * @param vector constant reference to a vector floating point number
 * representing input value
 * @param trainable_parameter scalar value controlling the behaviour of the
 * swish function
 * @return vector of floating point number containing the swish-transformed
 * value of the input vector
 *  - if the input vector is empty,an empty vector was returned
 *  - otherwise, the output vector has same size as the input vector, with each
 * element being the result of applying the swish function
 */
template <typename T>
inline std::vector<T> swish(const std::vector<T>& vector,
                            T                     trainable_parameter) {
  // make sure the type is a floating-point number
  static_assert(std::is_floating_point_v<T>,
                "swish only support floating-point number");

  if (vector.empty()) {
    return {};  // return empty vector if the input are empty
  }

  // pre-allocate the output vector with the same size as the input vector
  std::vector<T> output(vector.size());

  // aapply the swish function element-wise
  std::transform(
      vector.begin(),
      vector.end(),                                 // input range
      output.begin(),                               // output range
      [trainable_parameter](T x) -> T {             // lambda function for swish
        T scaled_x = trainable_parameter * x;       // scale input byte beta
        std::vector<T> sigmoid_input = {scaled_x};  // wraping scale x
        T              sigmoid_value = enola::function::sigmoid(
            sigmoid_input)[0];  // compute sigmoid value
        return x * sigmoid_value;
      });
  return output;
}

}  // namespace function
}  // namespace enola

#endif  // !FUNCTION_ACTIVATION_SWISH_HPP
