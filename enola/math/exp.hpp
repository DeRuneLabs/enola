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
 * computation will be stopping when the contribution of the current term become negligible
 * or when the max number of iterations is reached
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
    return std::numeric_limits<T>::infinity();
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

  // constant for taylor series approximation
  T result = T{1}; // start with the first term of the series
  T term   = T{1}; // current term in the series

  for (int i = 1; i < max_iteration; ++i) {
    term *= x / T(i); // update the term: term *= x / i
    result += term; // add the term to the result

    // stop if the term becomes negligible
    if (enola::math::abs(term) < epsilon * enola::math::abs(result)) {
      break;
    }
  }

  return result;
}
}  // namespace math
}  // namespace enola

#endif  // !MATH_EXP_HPP
