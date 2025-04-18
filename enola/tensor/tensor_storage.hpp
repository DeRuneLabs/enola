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
 * @brief Represent CPU device type.
 */
struct CPU {};

/**
 * @brief Represent GPU device type.
 */
struct GPU {};

/**
 * @brief Compute the total number of elements in a tensor based on its shape.
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

[[nodiscard]] inline std::size_t num_elements(
    const std::vector<std::size_t>& shape) noexcept {
  std::size_t result = 1;
  for (const auto& dim : shape) {
    result *= dim;
  }
  return result;
}

/**
 * @brief Primary template for tensor storage.
 */
template <typename T, typename Device>
struct Storage;

/**
 * @brief Specialization of `Storage` for CPU device.
 */
template <typename T>
struct Storage<T, CPU> {
  static_assert(std::is_trivially_copyable_v<T>,
                "Element type must be trivially copyable");

  using element_type = T;
  using storage_type = std::vector<element_type>;

  template <typename ShapeType>
  explicit Storage(const ShapeType& shape)
      : shape_(shape.begin(), shape.end()) {
    std::size_t total_elements = num_elements(shape_);
    if (total_elements == 0) {
      data.clear();
      return;
    }
    for (const auto& dim : shape_) {
      if (dim == 0) {
        throw std::invalid_argument("Shape must have non-zero dimensions");
      }
    }
    data.resize(total_elements, T{});
  }

  [[nodiscard]] constexpr T& operator[](std::size_t i) noexcept(false) {
#ifdef DEBUG
    if (i >= data.size()) {
      throw std::out_of_range("Index out of range");
    }
#endif
    return data[i];
  }

  [[nodiscard]] constexpr const T& operator[](std::size_t i) const
      noexcept(false) {
#ifdef DEBUG
    if (i >= data.size()) {
      throw std::out_of_range("Index out of range");
    }
#endif
    return data[i];
  }

  [[nodiscard]] constexpr std::size_t size() const noexcept {
    return data.size();
  }

  [[nodiscard]] constexpr const std::vector<std::size_t>& shape()
      const noexcept {
    return shape_;
  }

  template <typename ShapeType>
  void resize(const ShapeType& new_shape) {
    shape_.assign(new_shape.begin(), new_shape.end());
    std::size_t new_size = num_elements(shape_);
    if (new_size == 0) {
      throw std::invalid_argument("New shape must have non-zero dimensions");
    }
    data.resize(new_size, T{});
  }

 private:
  std::vector<std::size_t> shape_;
  storage_type data;
};

/**
 * @brief Specialization of `Storage` for GPU device.
 */
template <typename T>
struct Storage<T, GPU> {
  static_assert(std::is_trivially_copyable_v<T>,
                "Element type must be trivially copyable");

  using element_type = T;

  template <typename ShapeType>
  explicit Storage(const ShapeType& shape)
      : shape_(convert_to_vector(shape)) {
    std::size_t total_elements = num_elements(shape_);
    if (total_elements == 0) {
      throw std::invalid_argument("Shape must have non-zero dimensions");
    }
    try {
      gpu_init_ = std::make_unique<enola::utils::GPUInit>();
      cl_context context = gpu_init_->getContext();
      cl_int err;
      buffer_ = clCreateBuffer(context,
                               CL_MEM_READ_WRITE,
                               sizeof(T) * total_elements,
                               nullptr,
                               &err);
      if (err != CL_SUCCESS) {
        throw std::runtime_error("Failed to allocate GPU memory");
      }
    } catch (const std::exception& error) {
      throw std::runtime_error("GPU initialization failed: " +
                               std::string(error.what()));
    }
  }

  ~Storage() {
    if (buffer_) {
      clReleaseMemObject(buffer_);
    }
  }

  [[nodiscard]] T operator[](std::size_t i) const noexcept(false) {
#ifdef DEBUG
    if (i >= size()) {
      throw std::out_of_range("Index out of range");
    }
#endif
    T value;
    cl_int err;
    cl_command_queue queue = gpu_init_->getCommandQueue();
    err = clEnqueueReadBuffer(queue, buffer_, CL_TRUE, i * sizeof(T),
                              sizeof(T), &value, 0, nullptr, nullptr);
    if (err != CL_SUCCESS) {
      throw std::runtime_error("Failed to read from GPU memory");
    }
    return value;
  }

  void setElement(std::size_t i, const T& value) noexcept(false) {
#ifdef DEBUG
    if (i >= size()) {
      throw std::out_of_range("Index out of range");
    }
#endif
    cl_int err;
    cl_command_queue queue = gpu_init_->getCommandQueue();
    err = clEnqueueWriteBuffer(queue, buffer_, CL_TRUE, i * sizeof(T),
                               sizeof(T), &value, 0, nullptr, nullptr);
    if (err != CL_SUCCESS) {
      throw std::runtime_error("Failed to write to GPU memory");
    }
  }

  template <typename ShapeType>
  void resize(const ShapeType& new_shape) {
    std::vector<std::size_t> new_shape_vec = convert_to_vector(new_shape);
    std::size_t new_size = num_elements(new_shape_vec);
    if (new_size == 0) {
      throw std::invalid_argument("New shape must have non-zero dimensions");
    }
    if (buffer_) {
      clReleaseMemObject(buffer_);
      buffer_ = nullptr;
    }
    cl_int err;
    buffer_ = clCreateBuffer(gpu_init_->getContext(),
                             CL_MEM_READ_WRITE,
                             sizeof(T) * new_size,
                             nullptr,
                             &err);
    if (err != CL_SUCCESS) {
      throw std::runtime_error("Failed to allocate GPU memory during resize");
    }
    shape_ = std::move(new_shape_vec);
  }

  [[nodiscard]] constexpr std::size_t size() const noexcept {
    return num_elements(shape_);
  }

  [[nodiscard]] constexpr const std::vector<std::size_t>& shape()
      const noexcept {
    return shape_;
  }

 private:
  template <typename ShapeType>
  static std::vector<std::size_t> convert_to_vector(const ShapeType& shape) {
    return std::vector<std::size_t>(shape.begin(), shape.end());
  }

  std::vector<std::size_t> shape_;
  cl_mem buffer_ = nullptr;
  std::unique_ptr<enola::utils::GPUInit> gpu_init_;
};

/**
 * @brief Dynamic storage for tensors that automatically switches between CPU and GPU.
 */
template <typename T>
class DynamicStorage {
 public:
  using element_type = T;

  template <typename ShapeType>
  explicit DynamicStorage(const ShapeType& shape) {
    if (is_gpu_available()) {
      try {
        gpu_storage_ = std::make_unique<Storage<T, GPU>>(shape);
      } catch (const std::exception& error) {
        throw std::runtime_error("GPU storage initialization failed: " +
                                 std::string(error.what()));
      }
    } else {
      cpu_storage_ = std::make_unique<Storage<T, CPU>>(shape);
    }
  }

  [[nodiscard]] T operator[](std::size_t i) const noexcept(false) {
    if (gpu_storage_) {
      return (*gpu_storage_)[i];
    } else {
      return (*cpu_storage_)[i];
    }
  }

  void setElement(std::size_t i, const T& value) noexcept(false) {
    if (gpu_storage_) {
      gpu_storage_->setElement(i, value);
    } else {
      (*cpu_storage_)[i] = value;
    }
  }

  [[nodiscard]] constexpr std::size_t size() const noexcept {
    if (gpu_storage_) {
      return gpu_storage_->size();
    } else {
      return cpu_storage_->size();
    }
  }

  [[nodiscard]] constexpr const std::vector<std::size_t>& shape()
      const noexcept {
    if (gpu_storage_) {
      return gpu_storage_->shape();
    } else {
      return cpu_storage_->shape();
    }
  }

  template <typename ShapeType>
  void resize(const ShapeType& new_shape) {
    if (gpu_storage_) {
      gpu_storage_->resize(new_shape);
    } else {
      cpu_storage_->resize(new_shape);
    }
  }

 private:
  bool is_gpu_available() {
    try {
      auto gpu_init = std::make_unique<enola::utils::GPUInit>();
      return true;
    } catch (...) {
      return false;
    }
  }

  std::unique_ptr<Storage<T, GPU>> gpu_storage_;
  std::unique_ptr<Storage<T, CPU>> cpu_storage_;
};

}  // namespace tensor
}  // namespace enola

#endif  // !TENSOR_TENSOR_STORAGE_HPP
