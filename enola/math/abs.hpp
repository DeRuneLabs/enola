#ifndef MATH_ABS_HPP
#define MATH_ABS_HPP

#include "../tensor/tensor_storage.hpp"
#include <type_traits>

namespace enola {
namespace math {

/**
 * @brief compute the absolute value of a single numeric element
 *
 * this function calculate the absolute value of given number
 *
 * @tparam T type input value must be numeric type
 * @param value input value whose absolute value is to be computed
 * @return absolute value of the input value
 */
template <typename T>
[[nodiscard]] constexpr auto abs(T value) noexcept {
  // make sure T was numeric data tpe
  static_assert(std::is_arithmetic_v<T>, "element type must be numeric type");

  // use if constexpr to handle unsigned types separately
  // unsigned types are always non-negative, so their absolute value is the
  // value itself
  if constexpr (std::is_unsigned_v<T>) {
    return value;  // return value as-is for unsigned types
  } else {
    // for signed, use ternary operator to compute the abs value
    return (value < T{0}) ? -value : value;
  }
}

/**
 * @brief compute the absolute value of each element in the input tensor
 *
 * this function create a new tensor each element is the absolute value
 * of the corresponding element in the input tensor. the operation is perfomed
 * on the CPU device
 *
 * @tparam T type of elements stored in the tensor. must be numeric type
 * @param input the input tensor whose elements are to be transformed
 * @return new tensor containing the absolute value of the input tensor element
 */
template <typename T>
[[nodiscard]] inline enola::tensor::Storage<T, enola::tensor::CPU> abs(
    const enola::tensor::Storage<T, enola::tensor::CPU>& input) {
  // make sure T is numeric type
  static_assert(std::is_arithmetic_v<T>, "element type must be numeric type");

  // create new storage object with the same shape as the input tensor
  // wrap size of the input tensor in std::vector to represent shape
  // this make sure compatiblity with the storage constructor, which aexpect a
  // shape
  std::vector<std::size_t>                      shape = {input.size()};
  enola::tensor::Storage<T, enola::tensor::CPU> result(shape);

  // iterate over element in input tensor
  // compute the absolute value of each element using abs_value function
  for (std::size_t i = 0; i < input.size(); ++i) {
    result[i] = abs(input[i]);
  }
  return result;
}

}  // namespace math
}  // namespace enola

#endif  // !MATH_ABS_HPP
