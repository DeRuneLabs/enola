#ifndef FUNCTION_ACTIVATION_BINARY_STEP_HPP
#define FUNCTION_ACTIVATION_BINARY_STEP_HPP

#include <stdexcept>
#include <vector>
namespace enola {
namespace function {

/**
 * @brief implement binary step function
 *
 * this function applie the binary step operation to each element of the input
 * vector for each element in the vector
 * - if the element is greater than or equal to 0, its replace 1
 * - otherwise, will be replace 0
 *
 * @tparam T data type of the element in the vector
 * @param vector vector with numeric values
 * @return std::vector<T> new vector with the binary step function applied
 */
template <typename T>
std::vector<int> binary_step(const std::vector<T>& vector) {
  // validate the input vector
  if (vector.empty()) {
    throw std::invalid_argument("input argument cannot be empty");
  }

  // result vector to store the binary step values
  std::vector<int> result;
  // pre-allocate memory for efficiency
  result.reserve(vector.size());

  // apply binary step logical eval
  for (const auto& value : vector) {
    result.push_back(value >= 0 ? 1 : 0);
  }

  return result;
}
}  // namespace function
}  // namespace enola

#endif  // !FUNCTION_ACTIVATION_BINARY_STEP_HPP
