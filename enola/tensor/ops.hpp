#ifndef TENSOR_OPS_HPP
#define TENSOR_OPS_HPP

#include "tensor_storage.hpp"
#include <iostream>
#include <stdexcept>

#ifndef DEBUG
#define DEBUG 0
#endif  // !DEBUG

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
    const enola::tensor::Storage<T, enola::tensor::CPU>& storage) {
  // shape is inferred from the size of the tensor
  return {storage.size()};
}

template <typename T>
[[nodiscard]] std::vector<std::size_t> get_shape(
    const enola::tensor::Storage<T, enola::tensor::GPU>& storage) {
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
template <typename T, typename Device>
[[nodiscard]] enola::tensor::Storage<T, Device> add(
    const enola::tensor::Storage<T, Device>& lhs,
    const enola::tensor::Storage<T, Device>& rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::invalid_argument(
        "tensor must have the same size for element-wise");
  }

  auto                              shape = get_shape(lhs);
  enola::tensor::Storage<T, Device> result(shape);

  if constexpr (DEBUG) {
    std::cout << "[DEBUG] perform element-wise addition memory usage: "
              << result.size() * sizeof(T) << "bytes\n";
  }

  for (std::size_t i = 0; i < lhs.size(); ++i) {
#if DEBUG
    if (i >= lhs.size() || i >= rhs.size()) {
      throw std::out_of_range(
          "index out of range during element wise addition")''
    }
#endif  // DEBUG
    result[i] = lhs[i] + rhs[i];
  }
  return result;
}

/**
 * @brief perform element-wise substraction of two tensor
 *
 * subtract corresponding elemnt of two tensor and stores the result new tensor
 *
 * @tparam T type of element stored in the tensors
 * @param lhs left hand side tensor
 * @param rhs right hand side tensor
 * @return new tensor containing the result of the substract
 */
template <typename T, typename Device>
[[nodiscard]] enola::tensor::Storage<T, CPU> subtract(
    const enola::tensor::Storage<T, Device>& lhs,
    const enola::tensor::Storage<T, Device>& rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::invalid_argument(
        "tensor must have the same size for element-wise");
  }

  auto                              shape = get_shape(lhs);
  enola::tensor::Storage<T, Device> result(shape);

  if constexpr (DEBUG) {
    std::cout << "[DEBUG] perform element-wise subtract. memory usage: "
              << result.size() * sizeof(T) << " bytes\n";
  }

  for (std::size_t i = 0; i < lhs.size(); ++i) {
#if DEBUG
    if (i >= lhs.size() || i >= rhs.size()) {
      throw std::out_of_range("index of range during element-wise subtraction");
    }
#endif  // DEBUG
    result[i] = lhs[i] - rhs[i];
  }

  return result;
}

/**
 * @brief perform element-wise multiplication two tensor
 *
 * multiply corresponding element of two tensor and store the result in a new
 * tensor
 *
 * @tparam T type of element stored in the tensor
 * @param lhs left-hand side tensor
 * @param rhs right-hand side tensor
 * @return new tensor containing the result of multiplication
 */
template <typename T, typename Device>
[[nodiscard]] enola::tensor::Storage<T, Device> multiply(
    const enola::tensor::Storage<T, Device>& lhs,
    const enola::tensor::Storage<T, Device>& rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::invalid_argument(
        "tensor must have the same size for element-wise");
  }

  auto                              shape = get_shape(lhs);
  enola::tensor::Storage<T, Device> result(shape);

  if constexpr (DEBUG) {
    std::cout << "[DEBUG] perform element-wise multiplication, memory usage: "
              << result.size() * sizeof(T) << " bytes\n";
  }

  for (std::size_t i = 0; i < lhs.size(); ++i) {
#if DEBUG
    if (i >= lhs.size() || i >= rhs.size()) {
      throw std::out_of_range(
          "index out of range during element-wise multiplication");
    }
#endif  // DEBUG
    result[i] = lhs[i] * rhs[i];
  }
  return result;
}

/**
 * @brief perform element-wise division of two tensor
 *
 * divide corresponding element of two tensor and store the result in new tensor
 *
 * @tparam T type of elements stored in the tensor
 * @param lhs left hand side tensor
 * @param rhs the right hand side tensor
 * @return new tensor containing the result of the division
 */
template <typename T, typename Device>
[[nodiscard]] enola::tensor::Storage<T, Device> divide(
    const enola::tensor::Storage<T, Device>& lhs,
    const enola::tensor::Storage<T, Device>& rhs) {
  if (lhs.size() != rhs.size()) {
    throw std::invalid_argument(
        "tensor must have the same size for element-wise");
  }

  auto                              shape = get_shape(lhs);
  enola::tensor::Storage<T, Device> result(shape);

  if constexpr (DEBUG) {
    std::cout << "[DEBUG] perform element-wise division, memory usage: "
              << result.size() * sizeof(T) << " bytes\n";
  }

  for (std::size_t i = 0; i < lhs.size(); ++i) {
#if DEBUG
    if (i >= lhs.size() || i >= rhs.size()) {
      throw std::out_of_range(
          "index out of range during element wise division");
    }
#endif  // DEBUG
    if (rhs[i] == 0) {
      throw std::domain_error("division by zero during element-wise divide");
    }
    result[i] = lhs[i] / rhs[i];
  }
  return result;
}

/**
 * @brief computing the sum of all sum in element tensor
 *
 * @tparam T type of elements stored in the tensor
 * @param tensor input tensor
 * @return sum of all elements in the tensor
 */
template <typename T, typename Device>
[[nodiscard]] T sum(const enola::tensor::Storage<T, Device>& tensor) {
  T result = 0;
  for (std::size_t i = 0; i < tensor.size(); ++i) {
    result += tensor[i];
  }
  return result;
}

/**
 * @brief compute the mean of all elements in a tensor
 *
 * @tparam T type of elements stored in the tensor
 * @param tensor input tensor
 * @return mean of all elements in the tensor
 */
template <typename T, typename Device>
[[nodiscard]] double mean(const enola::tensor::Storage<T, Device>& tensor) {
  if (tensor.size() == 0) {
    throw std::invalid_argument("cannot compute mean of any empty tensor");
  }
  return static_cast<double>(sum(tensor)) / tensor.size();
}

}  // namespace tensor
}  // namespace enola

#endif  // !TENSOR_OPS_HPP
