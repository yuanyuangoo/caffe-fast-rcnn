#ifndef CAFFE_SYNCEDMEM_HPP_
#define CAFFE_SYNCEDMEM_HPP_

#include <cstdlib>

<<<<<<< HEAD
#ifdef USE_MKL
  #include "mkl.h"
#endif

#include "caffe/common.hpp"

namespace caffe {

// If CUDA is available and in GPU mode, host memory will be allocated pinned,
// using cudaMallocHost. It avoids dynamic pinning for transfers (DMA).
// The improvement in performance seems negligible in the single GPU case,
// but might be more significant for parallel training. Most importantly,
// it improved stability for large models on many GPUs.
inline void CaffeMallocHost(void** ptr, size_t size, bool* use_cuda) {
#ifndef CPU_ONLY
  if (Caffe::mode() == Caffe::GPU) {
    CUDA_CHECK(cudaMallocHost(ptr, size));
    *use_cuda = true;
    return;
  }
#endif
#ifdef USE_MKL
  *ptr = mkl_malloc(size ? size:1, 64);
#else
  *ptr = malloc(size);
#endif
  *use_cuda = false;
  CHECK(*ptr) << "host allocation of size " << size << " failed";
}

inline void CaffeFreeHost(void* ptr, bool use_cuda) {
#ifndef CPU_ONLY
  if (use_cuda) {
    CUDA_CHECK(cudaFreeHost(ptr));
    return;
  }
#endif
#ifdef USE_MKL
  mkl_free(ptr);
#else
  free(ptr);
#endif
=======
#include "caffe/common.hpp"
#include "caffe/util/math_functions.hpp"

namespace caffe {

// Theoretically, CaffeMallocHost and CaffeFreeHost should simply call the
// cudaMallocHost and cudaFree functions in order to create pinned memory.
// However, those codes rely on the existence of a cuda GPU (I don't know
// why that is a must since allocating memory should not be accessing the
// GPU resource, but it just creates an error as of Cuda 5.0) and will cause
// problem when running on a machine without GPU. Thus, we simply define
// these two functions for safety and possible future change if the problem
// of calling cuda functions disappears in a future version.
//
// In practice, although we are creating unpinned memory here, as long as we
// are constantly accessing them the memory pages almost always stays in
// the physical memory (assuming we have large enough memory installed), and
// does not seem to create a memory bottleneck here.

inline void CaffeMallocHost(void** ptr, size_t size) {
  *ptr = malloc(size);
  CHECK(*ptr) << "host allocation of size " << size << " failed";
}

inline void CaffeFreeHost(void* ptr) {
  free(ptr);
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
}


/**
 * @brief Manages memory allocation and synchronization between the host (CPU)
 *        and device (GPU).
 *
 * TODO(dox): more thorough description.
 */
class SyncedMemory {
 public:
<<<<<<< HEAD
  SyncedMemory();
  explicit SyncedMemory(size_t size);
=======
  SyncedMemory()
      : cpu_ptr_(NULL), gpu_ptr_(NULL), size_(0), head_(UNINITIALIZED),
        own_cpu_data_(false) {}
  explicit SyncedMemory(size_t size)
      : cpu_ptr_(NULL), gpu_ptr_(NULL), size_(size), head_(UNINITIALIZED),
        own_cpu_data_(false) {}
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
  ~SyncedMemory();
  const void* cpu_data();
  void set_cpu_data(void* data);
  const void* gpu_data();
<<<<<<< HEAD
  void set_gpu_data(void* data);
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
  void* mutable_cpu_data();
  void* mutable_gpu_data();
  enum SyncedHead { UNINITIALIZED, HEAD_AT_CPU, HEAD_AT_GPU, SYNCED };
  SyncedHead head() { return head_; }
  size_t size() { return size_; }

<<<<<<< HEAD
#ifndef CPU_ONLY
  void async_gpu_push(const cudaStream_t& stream);
#endif

 private:
  void check_device();

=======
 private:
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
  void to_cpu();
  void to_gpu();
  void* cpu_ptr_;
  void* gpu_ptr_;
  size_t size_;
  SyncedHead head_;
  bool own_cpu_data_;
<<<<<<< HEAD
  bool cpu_malloc_use_cuda_;
  bool own_gpu_data_;
  int device_;
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

  DISABLE_COPY_AND_ASSIGN(SyncedMemory);
};  // class SyncedMemory

}  // namespace caffe

#endif  // CAFFE_SYNCEDMEM_HPP_
