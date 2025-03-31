#ifndef FUNCTION_SIGMOID_HPP
#define FUNCTION_SIGMOID_HPP

#include <algorithm>
#include <cmath>
#include <type_traits>
#include <vector>

#ifdef _WIN32
#include <cstdlib>
#include <intrin.h>
#define WINDOWS_PLATFORM
#endif

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
  // apply sigmoid function to each element of the input vector
  std::transform(m1.begin(),
                 m1.end(),        // input range
                 output.begin(),  // output range
                 [](T x) -> T {   // lambda function to compute sigmoid
                                  // try to avoiding overflow
                   if (x > T(100)) {
                     return T(1.0);
                   }
                   // try to avoiding underflow
                   if (x < T(-100)) {
                     return T(0.0);
                   }
#ifdef WINDOWS_PLATFORM
                  // windows platform using fabs for float number value
                  // to make sure consistent behaviour on platform
                   if (std::fabs(x) < std::numeric_limits<T>::epsilon()) {
                    return T(0.5); // approximate to near zero
                   }

                   #ifdef __AVX__
                    __m256 vx = _mm256_set_set1_ps(static_cast<float>(x));
                    __m256 vexp = _mm256_exp_ps(vx); // avx exp intrisc
                    return T(1.0) / (T(1.0) + static_cast<T>(__m256_cvtss_f32(vexp)));
                   #endif
#endif
                   return T(1.0) / (T(1.0) + std::exp(-x));
                 });
  return output;  // return the transformed vector
}
}  // namespace function
}  // namespace enola

#endif  // !FUNCTION_SIGMOID_HPP
