#ifndef TENSOR_TENSOR_STORAGE_HPP
#define TENSOR_TENSOR_STORAGE_HPP

#include "../utils/gpu_init.hpp"
#include <cstddef>
#include <memory>
#include <stdexcept>
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
 * @brief represent gpu device type
 *
 * this struct serve tag to indicate that storage or operating are intended for
 * execution on the GPU using OpenCL
 */
struct GPU {};

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
  explicit Storage(const ShapeType& shape)
      : shape_(shape.begin(), shape.end()) {
    std::size_t total_elements = num_elements(shape_);
    // allowing zero tensor (total_elements == 0)
    if (total_elements == 0) {
      data.clear();  // clear storage
      return;
    }
    // validating all dimension are non-zero
    for (const auto& dim : shape_) {
      if (dim == 0) {
        throw std::invalid_argument("shape must have non-zero dimension");
      }
    }

    data.resize(total_elements, T{});
  }

  /**
   * @brief accesses an element at the specified index
   *
   * provides mutable access to the element at the given index
   *
   * @param i the index of the element to access
   * @return reference to the element ate the specified index
   */
  [[nodiscard]] constexpr T& operator[](std::size_t i) noexcept(false) {
#ifdef DEBUG
    if (i >= data.size()) {
      throw std::out_of_range("index out of range");
    }
#endif  // DEBUG
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
  [[nodiscard]] constexpr const T& operator[](std::size_t i) const
      noexcept(false) {
#ifdef DEBUG
    if (i >= data.size()) {
      throw std::out_of_range("index out of range");
    }
#endif  // DEBUG
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

  /**
   * @brief get shape of the tensor
   *
   * @return const reference to the shape vector
   */
  [[nodiscard]] constexpr const std::vector<std::size_t>& shape()
      const noexcept {
    return shape_;
  }

  /**
   * @brief resize the tensor to new shape
   *
   * @tparam ShapeType type of the new shape
   * @param new_shape new shape of the tensor
   */
  template <typename ShapeType>
  void resize(const ShapeType& new_shape) {
    shape_.assign(new_shape.begin(), new_shape.end());
    std::size_t new_size = num_elements(shape_);
    if (new_size == 0) {
      throw std::invalid_argument("new shape must have non-zero dimension");
    }
    data.resize(new_size, T{});
  }

 private:
  std::vector<std::size_t> shape_;  // shape of the tensor
  storage_type             data;    // the underlying storage container
};

/**
 * @brief specialization of `Storage` for GPU device
 *
 * this specialization implementation tensor storage for the GPU device using
 * opencl, it manage memory allocation and deallocation on the GPU and provide
 * access to the underlying opencl buffer
 *
 * @tparam T type of element stored in the tensor
 */
template <typename T>
struct Storage<T, GPU> {
  /**
   * @brief make sure that element type is trivially copyable
   *
   * tensor element must be trivally copyable to make sure compatibility with
   * GPU memory operations
   */
  static_assert(std::is_trivially_copyable_v<T>,
                "element type must be trivially copyable");

  // type of element stored in the tensor
  using element_type = T;

  /**
   * @brief construct tensor stroage object with the given shape
   *
   * initialize storage with size equal to the total number of element in the
   * tensor, as determine by the shape, allocate memory on the GPU
   *
   * @tparam ShapeType of the shape
   * @param shape the shape of the tensor
   */
  template <typename ShapeType>
  explicit Storage(const ShapeType& shape) : shape_(convert_to_vector(shape)) {
    std::size_t total_elements = num_elements(shape_);
    if (total_elements == 0) {
      throw std::invalid_argument("shape must have non-zero dimension");
    }

    try {
      // initialize GPU
      gpu_init_ = std::make_unique<enola::utils::GPUInit>();
      // get opencl context
      cl_context context = gpu_init_->getContext();
      // get opencl device
      cl_device_id device_id = gpu_init_->getDeviceID();

      cl_int err;
      buffer_ = clCreateBuffer(context,
                               CL_MEM_READ_WRITE,
                               sizeof(T) * total_elements,
                               nullptr,
                               &err);
      if (err != CL_SUCCESS) {
        throw std::runtime_error("failed to allocate GPU memory");
      }
    } catch (const std::exception& error) {
      throw std::runtime_error("gpu initialization fail: " +
                               std::string(error.what()));
    }
  }

  /**
   * @brief destructor release GPU resource
   *
   * make sure proper cleanup of the opencl buffer to avoid memory leak problem
   */
  ~Storage() {
    if (buffer_) {
      clReleaseMemObject(buffer_);  // release opencl buffer
    }
  }

  /**
   * @brief retrieve opencl buffer objec5
   *
   * @return opencl buffer associated with tensor storage
   */
  [[nodiscard]] cl_mem getBuffer() const noexcept { return buffer_; }

  /**
   * @brief return total number of element in the storage
   *
   * @return size of the storage
   */
  [[nodiscard]] constexpr std::size_t size() const noexcept {
    return num_elements(shape_);
  }

  /**
   * @brief retrieve shape of the tensor
   *
   * @return const reference to the shape vector
   */
  [[nodiscard]] constexpr const std::vector<std::size_t>& shape()
      const noexcept {
    return shape_;
  }

 private:
  template <typename ShapeType>
  static std::vector<std::size_t> convert_to_vector(const ShapeType& shape) {
    return std::vector<std::size_t>(shape.begin(), shape.end());
  }
  std::vector<std::size_t>               shape_;
  cl_mem                                 buffer_ = nullptr;
  std::unique_ptr<enola::utils::GPUInit> gpu_init_;
};

}  // namespace tensor
}  // namespace enola

#endif  // !TENSOR_TENSOR_STORAGE_HPP
