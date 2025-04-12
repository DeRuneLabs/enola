#ifndef TENSOR_TENSOR_STORAGE_HPP
#define TENSOR_TENSOR_STORAGE_HPP

#include "../utils/gpu_init.hpp"
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
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

  [[nodiscard]] T operator[](std::size_t i) const noexcept(false) {
#ifdef DEBUG
    if (i >= size()) {
      throw std::out_of_range("index out of range");
    }
#endif  // DEBUG
    T                value;
    cl_int           err;
    cl_command_queue queue = gpu_init_->getCommandQueue();
    err                    = clEnqueueReadBuffer(queue,
                              buffer_,
                              CL_TRUE,
                              i * sizeof(T),
                              sizeof(T),
                              &value,
                              0,
                              nullptr,
                              nullptr);
    if (err != CL_SUCCESS) {
      throw std::runtime_error("failed to read from GPU memory");
    }
    return value;
  }

  [[nodiscard]] T& operator[](std::size_t i) noexcept(false) {
    #ifdef DEBUG
    if (i >= size()) {
      throw std::out_of_range("index out of range");
    }
    #endif // DEBUG
    
static T temp_value;
    cl_int err;
    cl_command_queue queue = gpu_init_->getCommandQueue();
    err = clEnqueueReadBuffer(queue, buffer_, CL_TRUE, i * sizeof(T), sizeof(T), &temp_value, 0, nullptr, nullptr);
    if (err != CL_SUCCESS) {
      throw std::runtime_error("failed to read from GPU memory");
    }
    
    return temp_value;
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

/**
 * @brief dynamic storage for tensors that automatically switch between CPU and
 * GPU
 *
 * the `DynamicStorage` class provide a unified interface for tensor storage,
 * dynamically selecting between CPU and GPU storage based on runtime
 * availability, if the GPU is available it using GPU storage; otherwise, it
 * falls back to CPU storage, this make sure max flexibelity and performance
 * without requiring static binding to a specific device type
 *
 * @tparam T type of elements stored in tensor
 */
template <typename T>
class DynamicStorage {
 public:
  /**
   * @brief alias for the type of elements stored in the tensor
   */
  using element_type = T;

  /**
   * @brief construct `DynamicStorage` object with the given shape
   *
   * this constructor initialize the storage based on the availability of the
   * GPU, if GPU was available, it create GPU storage; otherwise, it fall back
   * to GPU storage
   *
   * @tparam ShapeType type of the shape
   * @param shape shape of the tensor, representing it dimension
   *
   * @throws std::invald_argument if shape contain zero dimension
   * @thros std::runtime_error if GPU initialization fails and no fallback is
   * available
   */
  template <typename ShapeType>
  explicit DynamicStorage(const ShapeType& shape) {
    if (is_gpu_available()) {
      // gpu is available, initialize GPU storage
      try {
        gpu_storage_ = std::make_unique<Storage<T, GPU>>(shape);
      } catch (const std::exception& error) {
        throw std::runtime_error("GPU storage initialization failed: " +
                                 std::string(error.what()));
      }
    } else {
      // GPU is unavailable, fallback to CPU storage
      cpu_storage_ = std::make_unique<Storage<T, CPU>>(shape);
    }
  }

  /**
   * @brief access an element at the specified index
   *
   * providing mutable access to the element at the given flat index in the
   * underlying storage
   *
   * @param i flat index of the element to access
   * @return reference to the element at the specified index
   *
   * @throws std::out_of_range if the index is out of bounds
   */
  [[nodiscard]] constexpr T& operator[](std::size_t i) noexcept(false) {
    if (gpu_storage_) {
      return (*gpu_storage_)[i];
    } else {
      return (*cpu_storage_)[i];
    }
  }

  /**
   * @brief access an element at the specified index (read-only)
   *
   * providing read-only access to the element at the given flat index in the
   * underlying storage
   *
   * @param i flat index of the element to access
   * @return const reference to the element at the specified index
   *
   * @throws std::out_of_range if the index is out of bounds
   */
  [[nodiscard]] constexpr const T& operator[](std::size_t i) const
      noexcept(false) {
    if (gpu_storage_) {
      return (*gpu_storage_)[i];
    } else {
      return (*cpu_storage_)[i];
    }
  }

  /**
   * @brief return the total number of element in the storage
   *
   * @return size of the storage,  the total number of elements in the tensor
   */
  [[nodiscard]] constexpr std::size_t size() const noexcept {
    if (gpu_storage_) {
      return gpu_storage_->size();
    } else {
      return cpu_storage_->size();
    }
  }

  /**
   * @brief retrieve the shape of the tensor
   *
   * @return constant reference to the shape vector, representing the dimensions
   * of the tensor
   */
  [[nodiscard]] constexpr const std::vector<std::size_t>& shape()
      const noexcept {
    if (gpu_storage_) {
      return gpu_storage_->shape();
    } else {
      return cpu_storage_->shape();
    }
  }

  /**
   * @brief resize the tensor to a new shape
   *
   * this method resize the underlying storage to accomodate the new shape, if
   * GPU storage is active, it resize the GPU storage; otherwise, it resize the
   * CPU storage
   *
   * @tparam ShapeType the type of the new shape
   * @param new_shape new shape of the tensor
   *
   * @throws std::invalid_argument if the new shape contains zero dimension
   */
  template <typename ShapeType>
  void resize(const ShapeType& new_shape) {
    if (gpu_storage_) {
      gpu_storage_->resize(new_shape);
    } else {
      cpu_storage_->resize(new_shape);
    }
  }

 private:
  /**
   * @brief check whether GPU is available for use
   *
   * this method attempt to initialize the GPU using `GPUInit` function, if
   * success it indicates that the GPU is available; otherwise, if falls back to
   * CPU
   *
   * @return `true` if the GPU is available, `false` otherwise
   */
  bool is_gpu_available() {
    try {
      auto gpu_init = std::make_unique<enola::utils::GPUInit>();
      return true;  // GPU available if initialization suceeds
    } catch (...) {
      return false;  // GPU is unavailable
    }
  }

  /**
   * @brief pointer to the GPU storage
   *
   * this pointer holds HPU storage instance if the GPU is available
   * it is `nullptr` if the GPU is unavailable
   */
  std::unique_ptr<Storage<T, GPU>> gpu_storage_;

  /**
   * @brief pointer to the CPU storage
   *
   * this pointer holds the CPU storage instance if the GPU is unavailable
   * it is `nullptr` if the GPU is available
   */
  std::unique_ptr<Storage<T, CPU>> cpu_storage_;
};

}  // namespace tensor
}  // namespace enola

#endif  // !TENSOR_TENSOR_STORAGE_HPP
