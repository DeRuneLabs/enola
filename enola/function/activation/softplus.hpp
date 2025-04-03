#ifndef FUNCTION_ACTIVATION_SOFTPLUS_HPP
#define FUNCTION_ACTIVATION_SOFTPLUS_HPP

#include "../../math/exp.hpp"
#include "../../math/log.hpp"
#include <cmath>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace enola {
namespace function {

/**
 * @breif implementing softplus activation function
 *
 * the function is defined f(x) = ln(1 + e^x)
 * this implementation support various numeric data type end ensure memory
 * safety
 *
 * @param T numeric type
 * @param input vector numeric values representing the input array
 * @return std::vector<T> a vector containing the result of apllying the
 * softplus activation
 */
template <typename T>
std::vector<T> softplus(const std::vector<T>& input) {
  // make sure the input type is numeric
  static_assert(std::is_arithmetic<T>::value, "input type must be numeric");
  // create result vector with the same size as the input
  std::vector<T> result(input.size());

  // apply the softplus function element-wise
  for (size_t i = 0; i < input.size(); ++i) {
    result[i] = enola::math::log(1 + enola::math::exp(input[i]));
  }
  return result;
}

/**
 * @brief overload version of softplus that working with raw pointer
 *
 * this version ensure memory safety by requiring the caller to provide valid
 * size
 *
 * @tparam T numeric type
 * @param input pointer to the input array
 * @param size the number of element in the input array
 * @return std::unique_ptr<std::vector<T>> smart pointer to the result vector
 */
template <typename T>
std::unique_ptr<std::vector<T>> softplus(const T* input, size_t size) {
  // make sure the input type is numeric
  static_assert(std::is_arithmetic<T>::value, "input type must be numeric");

  // validate input parameter
  if (!input) {
    throw std::invalid_argument("input pointer cannot be null");
  }

  // create result vector and apply the softplus function
  auto result = std::make_unique<std::vector<T>>(size);
  for (size_t i = 0; i < size; ++i) {
    (*result)[i] = enola::math::log(1 + enola::math::exp(input[i]));
  }
  return result;
}

}  // namespace function
}  // namespace enola

#endif  // !FUNCTION_ACTIVATION_SOFTPLUS_HPP
