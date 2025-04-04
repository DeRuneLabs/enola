#ifndef MATH_LOG_HPP
#define MATH_LOG_HPP

#include "abs.hpp"
#include "exp.hpp"
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace enola {
namespace math {

/**
 * @brief compute the natural logarithm (ln(x)) with netwon-rapshon method
 *
 * this formula logarithm function
 * \[
 * \text{ln}(x) = y \quad \text{such that} \quad e^y = x
 * \]
 *
 * this implementation uses the Newton-Raphson iterative method to approximate
 * \(\text{ln}(x)\):
 * \[
 * y_{n+1} = y_n - \frac{e^{y_n} - x}{e^{y_n}}
 * \]
 *
 * @tparam T floating-point type
 * @param x input value
 * @return natural logarithm of the input value
 * @throws std::domain_error if input value non-positive
 */
template <typename T>
[[nodiscard]] inline T log(T x) noexcept(false) {
  // make sure type is floating point type
  static_assert(std::is_floating_point_v<T>,
                "log only support floating-point type");

  // validating input value
  if (x <= T{0}) {
    throw std::domain_error("log is undefined for non-positive values");
  }

  // initial guess for ln(x)
  T y = x > 1.0 ? T{1.0} : T{-1.0};

  // constant for numerical precision and iteration control
  constexpr T epsilon =
      std::numeric_limits<T>::epsilon();  // precision threshold
  constexpr int max_iterations = 100;     // max number of iteration

  for (int i = 0; i < max_iterations; ++i) {
    T exp_y = enola::math::exp(y);  // compute \(e^y\)
    T delta = (x - exp_y) / exp_y;
    y += delta;

    // stop if the change is negligible
    if (enola::math::abs(delta) < epsilon) {
      break;
    }
  }

  // return final estimate of ln(x)
  return y;
}
}  // namespace math
}  // namespace enola

#endif  // !MATH_LOG_HPP
