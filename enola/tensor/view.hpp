#ifndef TENSOR_VIEW_HPP
#define TENSOR_VIEW_HPP

#include "tensor_storage.hpp"

namespace enola {
namespace tensor {

/**
 * @brief non-owning view tensor data
 *
 * TensorView provide lightweight wrapper around the underlying tensor storage,
 * allwing flexible interpretation of the tadat without copying, support
 * reshaping, slicing and tranpose by redifining shape and strides
 *
 * @tparam T type elemtn stored in the tensor
 */
template <typename T>
class TensorView {
 public:
  /**
   * @brief alias for type element stored in tensor
   */
  using element_type = T;

  /**
   * @brief construct TensorView object
   *
   * @param storage reference to the underlying tensor storage. TensorView does
   * not own this storage; it simply referencing it
   * @param shape vector representing the new shape of the view, this define how
   * the data is logically organized
   * @param strides vector representing the strides for accessing elements
   *
   * @throws std::invalid_argument if the size of shape and stride does not
   * match
   * @throws std::out_of_range if the view exceeds the bounds of the underlying
   * storage
   */
  template <typename StorageType>
  TensorView(StorageType&                    storage,
             const std::vector<std::size_t>& shape,
             const std::vector<std::size_t>& strides)
      : storage_(&storage), shape_(shape), strides_(strides) {
    // make sure that number of dimension in shape matching number of strides
    if (shape.size() != strides.size()) {
      throw std::invalid_argument("shape and strides must have the same size");
    }
    // validating that view does not exceed the bounds of underlying storage
    validate_view();
  }

  /**
   * @brief access an element at the specified multi-dimensional indices
   *
   * @param indices vector of indices specifying the position in the tensor
   *
   * @return reference to the element at the specified position
   *
   * @throws std::invalid_argument if number of indices does not match the
   * number
   * @throws std::out_of_range if index is out of range for its corresponding
   * number
   */
  [[nodiscard]] constexpr T& operator()(
      const std::vector<std::size_t>& indices) {
    return (*storage_)[compute_flat_index(indices)];
  }

  /**
   * @access an element at the specified multi-dimensional indices (read-only)
   *
   * @param indices vector of indices specifying the position in the tensor.
   *
   * @return const reference to the element at the specified position
   *
   * @throw std::invalid_argument if the number of indices does not match the
   * number
   * @throw std::out_of_range if any index is out range for corresponding
   * dimension
   */
  [[nodiscard]] constexpr const T& operator()(
      const std::vector<std::size_t>& indices) const {
    return (*storage_)[compute_flat_index(indices)];
  }

  /**
   * @brief get the shape of the view
   *
   * @return const reference to the shape vector, which represents the logical
   * dimensions of the view
   */
  [[nodiscard]] constexpr const std::vector<std::size_t>& shape()
      const noexcept {
    return shape_;
  }

  /**
   * @brief get the strides of the view
   *
   * @return const reference to the strides vector, which defines the step size
   *         required to move between elements along each dimension
   */
  [[nodiscard]] constexpr const std::vector<std::size_t>& strides()
      const noexcept {
    return strides_;
  }

 private:
  /**
   * @brief reference to the underlying tensor storage
   *
   * TensorView does not own this storage, simply reference it
   */
  enola::tensor::Storage<T, enola::tensor::CPU>* storage_;
  /**
   * @brief the shape of the view
   *
   * this define the logical dimension of the tensor as seen trough this view
   */
  std::vector<std::size_t> shape_;
  /**
   * @brief stride of the view
   *
   * stride define the step size required to move between elements along each
   * dimension for example, in row-major order, strides are typically computed
   * as strides[i] = product of all dimensions after dimension i
   */
  std::vector<std::size_t> strides_;

  /**
   * @brief validate that view does not exceed the bounds of the underlying
   * storage
   *
   * this function make sure that the max possible index in the view does not
   * exist the size of underlying storage
   *
   * @throws std::out_of_range if the view exceeds the bounds of underlying
   * storage
   */
  void validate_view() const {
    std::size_t max_index = 0;
    // computing the max index by sum up the prodcut of (dim - 1) and stride
    for (std::size_t i = 0; i < shape_.size(); ++i) {
      max_index += (shape_[i] - 1) * strides_[i];
    }
    // checking if the max index is within the bounds of the underlying storage
    if (max_index >= storage_->size()) {
      throw std::out_of_range(
          "view exceed the bound of the underlying storage");
    }
  }

  /**
   * @brief compute the flat index in underlying storage from multi-dimensional
   * indices
   *
   * @param indices vector of indices specifying the position in the tensor,
   * size of `indices` must match the number of dimensions in `shape`
   *
   * @return flat index in the underlying storage
   *
   * @throws std::invalid_argument if the number of indices does not match the
   * number
   * @throws std::out_of_range if any index is out of range
   */
  [[nodiscard]] constexpr std::size_t compute_flat_index(
      const std::vector<std::size_t>& indices) const {
    // make sure that number of indices matches the number dimension
    if (indices.size() != shape_.size()) {
      throw std::invalid_argument(
          "number of indices must match the number of dimension");
    }

    // calculate the flat index using formula:
    // flat_index = sum(indices[i] * strides[i]) for all dimensions i
    std::size_t flat_index = 0;
    for (std::size_t i = 0; i < indices.size(); ++i) {
      if (indices[i] >= shape_[i]) {
        throw std::out_of_range("index out of range");
      }
      // add the contrib of the curretn index to flat index
      flat_index += indices[i] * strides_[i];
    }

    return flat_index;
  }
};
}  // namespace tensor
}  // namespace enola

#endif  // !TENSOR_VIEW_HPP
