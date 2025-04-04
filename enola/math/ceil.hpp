#ifndef MATH_CEIL_HPP
#define MATH_CEIL_HPP

#include "../tensor/tensor_storage.hpp"
#include <type_traits>

namespace enola {
namespace math {

/**
 * @brief compute ceil scalar value
 *
 * this function calculating smallest integer greater than or equal to the input
 * value it support both floating-point and integral value. for floating point
 * type, it using custom implementation to computing the ceil without relying on
 * external libraries
 *
 * @tparam T type input value. must be numeric type support customization via
 * argument dependent looking
 * @param x input value whose ceiling is to be computed
 * @return the celling of the input value
 */
template <typename T>
[[nodiscard]] constexpr T ceil(T x) noexcept {
  // make sure that input type is either numeric or support customization
  static_assert(std::is_arithmetic_v<T> || !std::is_arithmetic_v<T>,
                "element type must be numeric or support customization");

  // handling float number
  if constexpr (std::is_floating_point_v<T>) {
    // custom implement for floating point type
    // - convert `x` to an integer to get integer part
    // - check if is fractional part (`x - int(x) > 0`)
    // - add 1 if the fractional is a fractional part
    return static_cast<T>(int(x)) + (x - static_cast<T>(int(x)) > 0 ? 1 : 0);
  } else {
    // for integral type, return value as-is since its already `ceiling`
    return x;
  }
}

/**
 * @brief compute the ceiling of each element in the input tensor
 *
 * this function creates a new tensor where each element is the ceiling of the
 * corresponding element in the input tensor. the operation is performed on the
 * CPU device
 *
 * @tparam T type of elements stored in the tensor. must be numeric or support
 *           customization via ADL.
 * @param input input tensor whose elements are to be transformed
 * @return new tensor containing the ceiling values of the input tensor's
 * elements
 *
 * @note output tensor has the same size as the input tensor
 */
template <typename T>
[[nodiscard]] inline enola::tensor::Storage<T, enola::tensor::CPU> ceil(
    const enola::tensor::Storage<T, enola::tensor::CPU>& input) {
  // make sure that the input type is either numeric or supports customization
  static_assert(std::is_arithmetic_v<T> || !std::is_arithmetic_v<T>,
                "element typ must be numeric or support customization");

  // create shape vector with single dimension equal to the input tensor
  std::vector<std::size_t> shape = {input.size()};

  // create a new storage object with the same size as the input tensor
  enola::tensor::Storage<T, enola::tensor::CPU> result(shape);

  // iterate over all element in the input tensor
  for (std::size_t i = 0; i < input.size(); ++i) {
    // apply scalar `ceil` function to each element
    result[i] = ceil(input[i]);
  }
  // return transformed tensor
  return result;
}

}  // namespace math
}  // namespace enola

#endif  // !MATH_CEIL_HPP
