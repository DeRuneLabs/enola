#ifndef MATH_EXP_HPP
#define MATH_EXP_HPP

#include "abs.hpp"
#include <limits>
#include <type_traits>
namespace enola {
namespace math {

/**
 * @brief compute exponential function (e^x)
 *
 * this function calculating using taylor series exp
 * e^x = 1 + x + x ^ 2 / 2! + x ^ 3 / 3! + ...
 *
 * @tparam T floating point type
 * @param x input value
 * @return result of e^x
 */
template <typename T>
[[nodiscard]] inline T exp(T x) noexcept {
  // make sure T was floating point number or numeric
  static_assert(std::is_floating_point_v<T>,
                "exp only support floating number");

  // handle numerical for extreme value input
  if (x > T(80)) {
    // preventing overflow for positive values
    return std::numeric_limits<T>::max(); 
  }
  if (x < T(-80)) {
    // prevent underflow for large negative values
    return T(0.0);
  }

  // constant for taylor series approximation
  constexpr T epsilon =
      std::numeric_limits<T>::epsilon();  // precision threshold
  constexpr int max_iteration =
      200;  // max iteration to prevent infinite looping

  T result    = 1.0;  // start with the first term of series
  T term      = 1.0;  // current term in the series
  T factorial = 1.0;

  for (int i = 1; i < max_iteration; ++i) {
    factorial *= i;                 // compute factorial incrementally
    term *= x / static_cast<T>(i);  // update the term
    result += term;                 // add the term to the result

    // stop if term become negligible
    if (enola::math::abs(term) < epsilon) {
      break;
    }
  }
  return result;
}
}  // namespace math
}  // namespace enola

#endif  // !MATH_EXP_HPP
