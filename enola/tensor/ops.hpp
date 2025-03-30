#ifndef TENSOR_OPS_HPP
#define TENSOR_OPS_HPP

#include "tensor_storage.hpp"
#include <stdexcept>

namespace enola {
namespace tensor {

/**
 * @brief helper function to extract shape of tensor
 *
 * @tparam T type elements stored in tensor
 * @param storage input tensor
 * @return vector representing shape of the tensor
 */
template <typename T>
[[nodiscard]] std::vector<std::size_t> get_shape(
    const Storage<T, CPU>& storage) {
  // shape is inferred from the size of the tensor
  return {storage.size()};
}

/**
 * @brief perform element-wise add of two tensor
 *
 * add corresponding element if two tensor and store the result in new tensor
 *
 * @tparam T type of elements stored in the tensor
 * @param lhs the left hand side tensor
 * @param rhs the right-hand side tensor
 * @return new tensor containing the reuslt of the addition
 */
template <typename T>
[[nodiscard]] Storage<T, CPU> add(const Storage<T, CPU>& lhs,
                                  const Storage<T, CPU>& rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::invalid_argument(
        "tensor must have the same size for element-wise");
  }

  auto            shape = get_shape(lhs);
  Storage<T, CPU> result(shape);

  for (std::size_t i = 0; i < lhs.size(); ++i) {
    result[i] = lhs[i] + rhs[i];
  }
  return result;
}

template <typename T>
[[nodiscard]] Storage<T, CPU> subtract(const Storage<T, CPU>& lhs,
                                       const Storage<T, CPU>& rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::invalid_argument(
        "tensor must have the same size for element-wise");
  }

  auto            shape = get_shape(lhs);
  Storage<T, CPU> result(shape);

  for (std::size_t i = 0; i < lhs.size(); ++i) {
    result[i] = lhs[i] - rhs[i];
  }

  return result;
}

template <typename T>
[[nodiscard]] Storage<T, CPU> multiply(const Storage<T, CPU>& lhs,
                                       const Storage<T, CPU>& rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::invalid_argument(
        "tensor must have the same size for element-wise");
  }

  auto            shape = get_shape(lhs);
  Storage<T, CPU> result(shape);

  for (std::size_t i = 0; i < lhs.size(); ++i) {
    result[i] = lhs[i] * rhs[i];
  }
  return result;
}

template <typename T>
[[nodiscard]] Storage<T, CPU> divide(const Storage<T, CPU>& lhs,
                                     const Storage<T, CPU>& rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::invalid_argument(
        "tensor must have the same size for element-wise");
  }

  auto            shape = get_shape(lhs);
  Storage<T, CPU> result(shape);

  for (std::size_t i = 0; i < lhs.size(); ++i) {
    if (rhs[i] == 0) {
      throw std::domain_error("division by zero during element-wise divide");
    }
    result[i] = lhs[i] / rhs[i];
  }
  return result;
}

template <typename T>
[[nodiscard]] T sum(const Storage<T, CPU>& tensor) {
  T result = 0;
  for (std::size_t i = 0; i < tensor.size(); ++i) {
    result += tensor[i];
  }
  return result;
}

template <typename T>
[[nodiscard]] double mean(const Storage<T, CPU>& tensor) {
  if (tensor.size() == 0) {
    throw std::invalid_argument("cannot compute mean of any empty tensor");
  }
  return static_cast<double>(sum(tensor)) / tensor.size();
}

}  // namespace tensor
}  // namespace enola

#endif  // !TENSOR_OPS_HPP
