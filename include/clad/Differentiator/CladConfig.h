// This file defines configuration that is shared by various files

#ifndef CLAD_CONFIG_H
#define CLAD_CONFIG_H

#include <cstdlib>
#include <memory>

// Define CUDA_HOST_DEVICE attribute for adding CUDA support to
// clad functions
#ifdef __CUDACC__
#define CUDA_HOST_DEVICE __host__ __device__
#else
#define CUDA_HOST_DEVICE
#endif

#ifdef  __CUDACC__
template<typename T>
__device__ T* addressof(T& r) {
  return __builtin_addressof(r);
}
template<typename T>
__host__ T* addressof(T& r) {
  return std::addressof(r);
}
#else
template<typename T>
T* addressof(T& r) {
  return std::addressof(r);
}
#endif

#endif // CLAD_CONFIG_H
