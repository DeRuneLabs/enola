#ifndef TENSOR_TENSOR_STORAGE_HPP
#define TENSOR_TENSOR_STORAGE_HPP

#include <cstddef>
#include <type_traits>
#include <vector>

namespace enola {
namespace tensor {
/**
 * @brief represent CPU device type
 *
 * this struct will serve tag to indicate that the storage or operations are
 * itended for execution in cpu
 */
struct CPU {};

/**
 * @brief compute the total number of element in a tensor based on its shape
 *
 * this function calculate the product of all dimension in the given shape
 * which representing the total number of elements in a tensor
 *
 * @tparam N the number of dimension in the shape
 * @param shape an array representing the dimension of the tensor
 * @return total number of elements in the tensor
 */
template <std::size_t N>
[[nodiscard]] inline constexpr std::size_t num_elements(
    const std::array<std::size_t, N>& shape) noexcept {
  std::size_t result = 1;
  for (const auto& dim : shape) {
    result *= dim;
  }
  return result;
}

/**
 * @brief compute the total number of element in a tensor based on its shape
 *
 * this function calculate the product of all dimension in the given shape
 * which representing the total number of element in a tensor
 *
 * @param shape a vector representing the dimension of the tensor
 * @return total number of element in the tensor
 */
[[nodiscard]] inline std::size_t num_elements(
    const std::vector<std::size_t>& shape) noexcept {
  std::size_t result = 1;
  for (const auto& dim : shape) {
    result *= dim;
  }
  return result;
}

/**
 * @brief primary template for tensor storage
 *
 * this primary template declaration for the `Storage` class
 *
 * @tparam T the type of elements stored in the tensor
 * @tparam device the device type (e.g CPU) where tensor resides
 */
template <typename T, typename Device>
struct Storage;

/**
 * @brief specialization of `storage` for CPU device
 *
 * this specialization implement tensor storage for CPU device, it use vector as
 * the underlying storage container and proveides methods for accessing and
 * iterating over the elements
 *
 * @tparam T the type of elements stored in the tensor
 */
template <typename T>
struct Storage<T, CPU> {
  /**
   * @brief ensure that element type is trivally copyable
   *
   * tensor element must be trivially copyable to make sure compability with
   * low level memory operations
   */
  static_assert(std::is_trivially_copyable_v<T>,
                "element type must be trivially copyable");

  using element_type = T;  // type of element stored in tensor
  using storage_type =
      std::vector<element_type>;  // type of underlying storage container
  using iterator =
      typename storage_type::iterator;  // iterator type for mutable access to
                                        // elements
  using const_iterator =
      typename storage_type::const_iterator;  // type for read-onyl access to
                                              // elements

  /**
   * @brief construct tensor storage object with the given shape
   *
   * initialize the storage with a size equal to the total number of elements
   * in the tensor, as determined by the shape, all elements are initialized to
   * the default value of `T`
   *
   * @tparam ShapeType the type of the shape
   * @param shape the shape of the tensor
   */
  template <typename ShapeType>
  explicit Storage(const ShapeType& shape) : data(num_elements(shape), T{}) {}

  /**
   * @brief accesses an element at the specified index
   *
   * provides mutable access to the element at the given index
   *
   * @param i the index of the element to access
   * @return reference to the element ate the specified index
   */
  [[nodiscard]] constexpr T& operator[](std::size_t i) noexcept {
    return data[i];
  }

  /**
   * @brief access an element at the specified index
   *
   * proved read-only access to the element at the given index
   *
   * @param i the index of the element to access
   * @return const reference to the element at the specified index
   */
  [[nodiscard]] constexpr const T& operator[](std::size_t i) const noexcept {
    return data[i];
  }

  /**
   * @brief return an iterator to the beginning of the storage
   *
   * @return an iterator pointing to the first element in the storage
   */
  [[nodiscard]] constexpr iterator begin() noexcept { return data.begin(); }

  /**
   * @brief return an iterator to the end of the storage
   *
   * @return an iterator pointing to one past the last element in the storage
   */
  [[nodiscard]] constexpr iterator end() noexcept { return data.end(); }

  /**
   * @brief return a const iterator to the beginning of the storage
   *
   * @return const iterator pointing to the first element in the storage
   */
  [[nodiscard]] constexpr const iterator cbegin() const noexcept {
    return data.cbegin();
  }

  /**
   * @brief return const interator to the end of the storeage
   *
   * @return const iterator pointer to one past the last element in the storage
   */
  [[nodiscard]] constexpr const_iterator cend() const noexcept {
    return data.cend();
  }

  /**
   * @brief return the total number of elements in the storage
   *
   * @return the size of the storage
   */
  [[nodiscard]] constexpr std::size_t size() const noexcept {
    return data.size();
  }

 private:
  storage_type data;  // the underlying storage container
};

}  // namespace tensor
}  // namespace enola

#endif  // !TENSOR_TENSOR_STORAGE_HPP
