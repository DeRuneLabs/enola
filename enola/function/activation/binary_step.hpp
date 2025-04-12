#ifndef FUNCTION_ACTIVATION_BINARY_STEP_HPP
#define FUNCTION_ACTIVATION_BINARY_STEP_HPP

#include "../../tensor/view.hpp"
#include <iterator>
#include <stdexcept>
#include <type_traits>
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
 * @tparam Container data type of the element in the vector
 * @param vector vector with numeric values
 * @return std::vector<T> new vector with the binary step function applied
 */
template <typename Container>
auto binary_step(const Container& input) {
  // validate the input vector
  if (input.empty()) {
    throw std::invalid_argument("input argument cannot be empty");
  }

  // deduce value type of the input container
  using ValueType = typename std::decay_t<decltype(*std::begin(input))>;

  // create res container of the same type as the input
  Container result;

  // reserve memory if container support
  if constexpr (std::is_same_v<Container, std::vector<ValueType>>) {
    result.reserve(input.size());
  }

  //  apply binary step function to each element
  for (const auto& value : input) {
    result.push_back(value >= 0 ? 1 : 0);
  }
  return result;
}

/**
 * @brief specialization for tensorview
 *
 * applies the binary step function to a tensorflow, the result is stored in new
 * TensorView with the same shape and stride as input
 *
 * @tparam T type of element in tensor
 * @param input the input TensorView
 * @return new tensorview with binary step applied
 */
template <typename T>
enola::tensor::TensorView<T> binary_step(
    const enola::tensor::TensorView<T>& input) {
  // validating input
  if (input.shape().empty()) {
    throw std::invalid_argument("input tensorview cannot have an empty shape");
  }

  // create new storage object to hold the result
  auto* input_storage = &input.storage();
  auto  result_storage =
      std::make_unique<enola::tensor::DynamicStorage<T>>(input.shape());

  // apply binary step function for each element
  for (std::size_t i = 0; i < result_storage.size(); ++i) {
    result_storage[i] = input[i] >= 0 ? 1 : 0;
  }

  // return tensorview over the result storage
  return enola::tensor::TensorView<T>(
      result_storage, input.shape(), input.stride());
}

template <typename Container>
[[nodiscard]] std::vector<int> to_int_vector(const Container& container) {
  std::vector<int> result;
  result.reserve(container.size());
  for (const auto& value : container) {
    result.push_back(static_cast<int>(value));
  }
  return result;
}

}  // namespace function
}  // namespace enola

#endif  // !FUNCTION_ACTIVATION_BINARY_STEP_HPP
