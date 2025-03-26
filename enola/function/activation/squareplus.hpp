#ifndef FUNCTION_ACTIVATION_SQUAREPLUS_HPP
#define FUNCTION_ACTIVATION_SQUAREPLUS_HPP

#include <cmath>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace enola {
namespace function {

/**
 * @brief implement the SquarePlus activation function
 *
 * the SquarePlus function is defined as f(x) = (x + sqrt(x^2 + beta)) / 2
 * this implementation supports various numeric data types and ensures memory
 * safety
 *
 * @tparam T numeric type
 * @param input a vector numeri values representing the input array
 * @param beta vector value controlling the size of the curved region
 * @return std::vector<t> vector containing the result of applying the
 * squareplus activation function
 */
template <typename T>
std::vector<T> squareplus(const std::vector<T> &input, T beta) {
  // ensure the input type is numeric
  static_assert(std::is_arithmetic<T>::value, "input type must be numeric");

  // validate beta
  if (beta < 0) {
    throw std::invalid_argument("beta must be non-negative");
  }

  // create a result vector within the same size as the input
  std::vector<T> result(input.size());

  // apply the squareplus function element-wise
  for (size_t i = 0; i < input.size(); ++i) {
    result[i] = (input[i] + std::sqrt(input[i] * input[i] + beta)) / 2;
  }

  return result;
}

/**
 * @brief overloaded version of squareplus that works with raw pointers
 * this version ensures memory safety by requiring the caller to provide valid
 * size information
 *
 * @tparam T numeric type
 * @param input a pointer to the input array
 * @param size the number of elements in the input array
 * @param beta scalar value controlling the size of the curved region
 * @return std::unique_ptr<std::vector<T>> smart pointer to the result vector
 */
template <typename T>
std::unique_ptr<std::vector<T>> squareplus(const T *input,
                                           size_t   size,
                                           T        beta) {
  // make sure the input the is numeric
  static_assert(std::is_arithmetic<T>::value, "input type must be numeric");

  // validate input parameter
  if (!input) {
    throw std::invalid_argument("input pointer cannot be null");
  }
  if (beta < 0) {
    throw std::invalid_argument("beta must be non-negative");
  }

  // create the result vector and apply the SquarePlus function
  auto result = std::make_unique<std::vector<T>>(size);
  for (size_t i = 0; i < size; ++i) {
    (*result)[i] = (input[i] + std::sqrt(input[i] * input[i] + beta)) / 2;
  }

  return result;
}

}  // namespace function
}  // namespace enola

#endif  // !FUNCTION_ACTIVATION_SQUAREPLUS_HPP
