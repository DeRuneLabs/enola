#ifndef FUNCTION_ACTIVATION_ELU_HPP
#define FUNCTION_ACTIVATION_ELU_HPP

#include "../../math/exp.hpp"
#include <stdexcept>
#include <vector>
namespace enola {
namespace function {

/**
 * @brief implementing exponential linear unit (ELU) activation function
 *
 * ELU formula define
 * f(x) = x, if x > 0
 * f(x) = alpha * (exp(x) - 1), if x <= 0
 * where alpha >= 0 is hyperparameter
 *
 * this function oeprate on vector of floating point number and applies the ELU
 *
 * @tparam T floating-point
 * @param input_vector input vector of value apply ELU activation
 * @param alpha hyperparameter controlling the slope for negative input
 * @return std::Vector<T> vector containing the ELU-trasnform values
 *
 * @throw std::invalid_argument if alpha is negative or input_vector are empty
 */
template <typename T>
std::vector<T> exponential_linear_unit(const std::vector<T>& input_vector,
                                       T                     alpha) {
  // validating the alpha number
  if (alpha < 0) {
    throw std::invalid_argument("alpha must be non-negative number");
  }

  // validating vector input
  if (input_vector.empty()) {
    throw std::invalid_argument("input vector cannot be empty");
  }

  // make output vector with same size as input
  std::vector<T> output_vector(input_vector.size());

  // applying the ELU activation function on element-wise
  for (size_t i = 0; i < input_vector.size(); ++i) {
    if (input_vector[i] > 0) {
      output_vector[i] = input_vector[i];  // f(x) = x for x > 0
    } else {
      output_vector[i] = alpha * (enola::math::exp(input_vector[i]) - 1);
    }
  }

  return output_vector;
}

}  // namespace function
}  // namespace enola

#endif  // !FUNCTION_ACTIVATION_ELU_HPP
