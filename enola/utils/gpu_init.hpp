#ifndef ENOLA_UTILS_GPU_INIT_HPP
#define ENOLA_UTILS_GPU_INIT_HPP

// NOTE: currently opencl default was 3.0
#define CL_TARGET_OPENCL_VERSION 300

#include <CL/cl.h>
#include <CL/cl_platform.h>

#include <cmath>
#include <stdexcept>
#include <vector>

namespace enola {
namespace utils {

/**
 * @brief utility class to initialize and manage opencl GPU resource
 *
 * this class encapsulate initialization of opencl platform, device and context,
 * make sure a valid gpu device is selected and provide access to opencl context
 * and device id for further use
 */
class GPUInit {
 public:
  /**
   * @brief constructor intialize the opencl environment
   *
   * initialize the opencl platform, device, context, and command queue, the
   * constructor perform the following steps
   * - retrieve the first available opencl platform
   * - select the first available GPU device from the platform
   * - create an opencl context for the selected GPU device
   * - create an opencl command for executing operation on GPU
   *
   * @throws std::runtime_error if any step in the initialization process fails
   */
  GPUInit() {
    cl_int err;

    // retrieve the first available opencl platform
    err = clGetPlatformIDs(1, &platform_id, nullptr);
    if (err != CL_SUCCESS) {
      throw std::runtime_error("failed to get opencl platform");
    }

    // retrieve the first available GPU device from the platform
    err =
        clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, nullptr);
    if (err != CL_SUCCESS) {
      throw std::runtime_error("failed to get opencl device");
    }

    // create an opencl context for the selected GPU device
    context = clCreateContext(nullptr, 1, &device_id, nullptr, nullptr, &err);
    if (err != CL_SUCCESS) {
      throw std::runtime_error("failed to create opencl context");
    }

    // create an opencl command queue for executing operations on the GPU
    const cl_queue_properties properties[] = {0};
    command_queue_                         = clCreateCommandQueueWithProperties(
        context, device_id, properties, &err);
    if (err != CL_SUCCESS) {
      throw std::runtime_error("failed to create opencl command queue");
    }
  }

  /**
   * @brief destructor release opencl resource
   *
   * make sure proper cleanup of the opencl context and device to avoid memory
   * leak problem
   */
  ~GPUInit() {
    if (context) {
      // release opencl context
      clReleaseContext(context);
    }
    if (device_id) {
      // release opencl device
      clReleaseDevice(device_id);
    }
  }

  /**
   * @brief get the initialized opencl context
   *
   * @return cl_context opencl context associated with the selected GPU device
   */
  cl_context getContext() const { return context; }

  /**
   * @brief get the selected opencl device ID
   *
   * @return cl_device_id opencl device id of the selected GPU
   */
  cl_device_id getDeviceID() const { return device_id; }

  /**
   * @brief retrieve opencl command queue
   *
   * @return the opencl command queue associated with GPU
   */
  [[nodiscard]] cl_command_queue getCommandQueue() const noexcept {
    return command_queue_;
  }

 private:
  cl_platform_id   platform_id    = nullptr;  // opencl platform id
  cl_device_id     device_id      = nullptr;  // opencl device id
  cl_context       context        = nullptr;  // opencl context for device
  cl_command_queue command_queue_ = nullptr;  // opencl command queue

  /**
   * @brief initialize opencl environment
   *
   * queries available opencl platform and device, select te first GPU device,
   * and create an opencl context for the selected device, this method is not
   * currently used in the constructor but can be reused for more complex
   * initialization logic
   *
   * - queries available opencl platform
   * - iterate through platform to find GPU device
   * - create opencl context for the selected GPU device
   *
   * @throws std::runtime_error if not opencl platform or GPU device is found,
   * or if context creation is fails
   */
  void initOpenCL() {
    cl_uint platform_count = 0;
    cl_int  err            = clGetPlatformIDs(0, nullptr, &platform_count);
    // check any opencl platform are available
    if (err != CL_SUCCESS || platform_count == 0) {
      throw std::runtime_error("no opencl platform found");
    }

    // retrieve list of available opencl platform
    std::vector<cl_platform_id> platforms(platform_count);
    err = clGetPlatformIDs(platform_count, platforms.data(), nullptr);
    if (err != CL_SUCCESS) {
      throw std::runtime_error("failed to retrieve opencl platform");
    }

    // iterate through platform to find a GPU device
    for (const auto& platform : platforms) {
      cl_uint device_count = 0;
      err                  = clGetDeviceIDs(
          platform, CL_DEVICE_TYPE_GPU, 0, nullptr, &device_count);
      // check if platform has any GPU device
      if (err == CL_SUCCESS && device_count > 0) {
        std::vector<cl_device_id> devices(device_count);
        err = clGetDeviceIDs(platform,
                             CL_DEVICE_TYPE_GPU,
                             device_count,
                             devices.data(),
                             nullptr);
        // if successful, select first GPU device on this platform
        if (err == CL_SUCCESS) {
          platform_id = platform;
          device_id   = devices[0];
          break;
        }
      }
    }

    // make sure valid GPU device found
    if (!device_id) {
      throw std::runtime_error("no opencl GPU device found");
    }

    // create opencl context for the slected GPU device
    context = clCreateContext(nullptr, 1, &device_id, nullptr, nullptr, &err);
    if (err != CL_SUCCESS) {
      throw std::runtime_error("failed to create opencl context");
    }
  }
};
}  // namespace utils
}  // namespace enola

#endif  // !ENOLA_UTILS_GPU_INIT_HPP
