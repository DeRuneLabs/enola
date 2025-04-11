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
   * call private `initOpenCL()` method to set opencl platform, device, and
   * context
   */
  GPUInit() { initOpenCL(); }

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

 private:
  cl_platform_id platform_id = nullptr;  // opencl platform id
  cl_device_id   device_id   = nullptr;  // opencl device id
  cl_context     context     = nullptr;  // opencl context for device

  /**
   * @brief initialize opencl environment
   *
   * - queries available opencl platform
   * - iterate through platform to find GPU device
   * - create opencl context for the selected GPU device
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
