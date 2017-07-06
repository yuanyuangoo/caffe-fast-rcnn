#ifdef USE_CUDNN
#include <vector>

<<<<<<< HEAD
#include "caffe/layers/cudnn_conv_layer.hpp"
=======
#include "caffe/filler.hpp"
#include "caffe/layer.hpp"
#include "caffe/util/im2col.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/vision_layers.hpp"
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

namespace caffe {

__global__ void sync_conv_groups() { }

template <typename Dtype>
void CuDNNConvolutionLayer<Dtype>::Forward_gpu(
    const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
<<<<<<< HEAD
  const Dtype* weight = this->blobs_[0]->gpu_data();
  for (int i = 0; i < bottom.size(); ++i) {
    const Dtype* bottom_data = bottom[i]->gpu_data();
    Dtype* top_data = top[i]->mutable_gpu_data();

    // Forward through cuDNN in parallel over groups.
    for (int g = 0; g < this->group_; g++) {
=======
  for (int i = 0; i < bottom.size(); ++i) {
    const Dtype* bottom_data = bottom[i]->gpu_data();
    Dtype* top_data = top[i]->mutable_gpu_data();
    const Dtype* weight = this->blobs_[0]->gpu_data();

    size_t workspace_limit_bytes = this->kernel_h_ *
                                   this->kernel_w_ *
                                   this->channels_ *
                                   sizeof(int) + 1;

    // Forward through cuDNN in parallel over groups.
    for (int g = 0; g < this->group_; g++) {
      cudnnConvolutionFwdAlgo_t algo;

      // pick the convolution algorithm
      // TODO(shelhamer) this should be done during reshape
      // TODO(shelhamer) the choice of automatic or manual algorithm picking
      // should be exposed in proto
      CUDNN_CHECK(cudnnGetConvolutionForwardAlgorithm(handle_[g],
        bottom_descs_[i],
        filter_desc_,
        conv_descs_[i],
        top_descs_[i],
        CUDNN_CONVOLUTION_FWD_SPECIFY_WORKSPACE_LIMIT,
        workspace_limit_bytes,  // memoryLimitInBytes,
        &algo));

      // get minimum size of the workspace needed for the desired algorithm
      size_t workspaceSizeInBytes_temp = 0;

      CUDNN_CHECK(cudnnGetConvolutionForwardWorkspaceSize(handle_[g],
        bottom_descs_[i],
        filter_desc_,
        conv_descs_[i],
        top_descs_[i],
        algo,
        &workspaceSizeInBytes_temp));

      if (workspaceSizeInBytes_temp > workspaceSizeInBytes) {
        workspaceSizeInBytes = workspaceSizeInBytes_temp;
        // free the existing workspace and allocate a new (larger) one
        cudaFree(this->workspace);
        cudaError_t err = cudaMalloc(&(this->workspace), workspaceSizeInBytes);
        if (err != cudaSuccess) {
          // force zero memory path
          algo = CUDNN_CONVOLUTION_FWD_ALGO_IMPLICIT_GEMM;
          workspace = NULL;
          workspaceSizeInBytes = 0;
        }
      }

>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
      // Filters.
      CUDNN_CHECK(cudnnConvolutionForward(handle_[g],
            cudnn::dataType<Dtype>::one,
            bottom_descs_[i], bottom_data + bottom_offset_ * g,
<<<<<<< HEAD
            filter_desc_, weight + this->weight_offset_ * g,
            conv_descs_[i],
            fwd_algo_[i], workspace[g], workspace_fwd_sizes_[i],
=======
            filter_desc_, weight + weight_offset_ * g,
            conv_descs_[i],
            algo, workspace, workspaceSizeInBytes,
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
            cudnn::dataType<Dtype>::zero,
            top_descs_[i], top_data + top_offset_ * g));

      // Bias.
      if (this->bias_term_) {
        const Dtype* bias_data = this->blobs_[1]->gpu_data();
<<<<<<< HEAD
        CUDNN_CHECK(cudnnAddTensor(handle_[g],
=======
        CUDNN_CHECK(cudnnAddTensor(handle_[g], CUDNN_ADD_SAME_C,
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
              cudnn::dataType<Dtype>::one,
              bias_desc_, bias_data + bias_offset_ * g,
              cudnn::dataType<Dtype>::one,
              top_descs_[i], top_data + top_offset_ * g));
      }
    }

    // Synchronize the work across groups, each of which went into its own
    // stream, by launching an empty kernel into the default (null) stream.
    // NOLINT_NEXT_LINE(whitespace/operators)
    sync_conv_groups<<<1, 1>>>();
  }
}

template <typename Dtype>
void CuDNNConvolutionLayer<Dtype>::Backward_gpu(const vector<Blob<Dtype>*>& top,
    const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
  const Dtype* weight = NULL;
  Dtype* weight_diff = NULL;
  if (this->param_propagate_down_[0]) {
    weight = this->blobs_[0]->gpu_data();
    weight_diff = this->blobs_[0]->mutable_gpu_diff();
  }
  Dtype* bias_diff = NULL;
  if (this->bias_term_ && this->param_propagate_down_[1]) {
    bias_diff = this->blobs_[1]->mutable_gpu_diff();
  }
  for (int i = 0; i < top.size(); ++i) {
    const Dtype* top_diff = top[i]->gpu_diff();
    // Backward through cuDNN in parallel over groups and gradients.
    for (int g = 0; g < this->group_; g++) {
      // Gradient w.r.t. bias.
      if (this->bias_term_ && this->param_propagate_down_[1]) {
        CUDNN_CHECK(cudnnConvolutionBackwardBias(handle_[0*this->group_ + g],
              cudnn::dataType<Dtype>::one,
              top_descs_[i],  top_diff + top_offset_ * g,
              cudnn::dataType<Dtype>::one,
              bias_desc_, bias_diff + bias_offset_ * g));
      }

      // Gradient w.r.t. weights.
      if (this->param_propagate_down_[0]) {
        const Dtype* bottom_data = bottom[i]->gpu_data();
<<<<<<< HEAD
        CUDNN_CHECK(cudnnConvolutionBackwardFilter(
              handle_[1*this->group_ + g],
=======
        CUDNN_CHECK(cudnnConvolutionBackwardFilter(handle_[1*this->group_ + g],
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
              cudnn::dataType<Dtype>::one,
              bottom_descs_[i], bottom_data + bottom_offset_ * g,
              top_descs_[i],    top_diff + top_offset_ * g,
              conv_descs_[i],
<<<<<<< HEAD
              bwd_filter_algo_[i], workspace[1*this->group_ + g],
              workspace_bwd_filter_sizes_[i],
              cudnn::dataType<Dtype>::one,
              filter_desc_, weight_diff + this->weight_offset_ * g));
=======
              cudnn::dataType<Dtype>::one,
              filter_desc_, weight_diff + weight_offset_ * g));
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
      }

      // Gradient w.r.t. bottom data.
      if (propagate_down[i]) {
        if (weight == NULL) {
          weight = this->blobs_[0]->gpu_data();
        }
        Dtype* bottom_diff = bottom[i]->mutable_gpu_diff();
<<<<<<< HEAD
        CUDNN_CHECK(cudnnConvolutionBackwardData(
              handle_[2*this->group_ + g],
              cudnn::dataType<Dtype>::one,
              filter_desc_, weight + this->weight_offset_ * g,
              top_descs_[i], top_diff + top_offset_ * g,
              conv_descs_[i],
              bwd_data_algo_[i], workspace[2*this->group_ + g],
              workspace_bwd_data_sizes_[i],
=======
        CUDNN_CHECK(cudnnConvolutionBackwardData(handle_[2*this->group_ + g],
              cudnn::dataType<Dtype>::one,
              filter_desc_, weight + weight_offset_ * g,
              top_descs_[i], top_diff + top_offset_ * g,
              conv_descs_[i],
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
              cudnn::dataType<Dtype>::zero,
              bottom_descs_[i], bottom_diff + bottom_offset_ * g));
      }
    }

    // Synchronize the work across groups, each of which went into its own
    // stream, by launching an empty kernel into the default (null) stream.
    // NOLINT_NEXT_LINE(whitespace/operators)
    sync_conv_groups<<<1, 1>>>();
  }
}

INSTANTIATE_LAYER_GPU_FUNCS(CuDNNConvolutionLayer);

}  // namespace caffe
#endif
