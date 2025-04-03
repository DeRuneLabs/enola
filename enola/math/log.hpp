#ifndef MATH_LOG_HPP
#define MATH_LOG_HPP

#include "abs.hpp"
#include "exp.hpp"
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace enola {
namespace math {

template <typename T>
[[nodiscard]] inline T log(T x) noexcept (false) {
  static_assert(std::is_floating_point_v<T>,
                "log only support floating-point type");

  if (x <= T{0}) {
    throw std::domain_error("log is undefined for non-positive values");
  }

  T y = x > 1.0 ? T{1.0} : T{-1.0};

  constexpr T   epsilon        = std::numeric_limits<T>::epsilon();
  constexpr int max_iterations = 100;

  for (int i = 0; i < max_iterations; ++i) {
    T exp_y = enola::math::exp(y);
    T delta = (x - exp_y) / exp_y;
    y += delta;

    if (enola::math::abs(delta) < epsilon) {
      break;
    }
  }

  return y;
}
}  // namespace math
}  // namespace enola

#endif  // !MATH_LOG_HPP
