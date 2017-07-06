#include <vector>

<<<<<<< HEAD
#include "caffe/layers/deconv_layer.hpp"
=======
#include "caffe/filler.hpp"
#include "caffe/layer.hpp"
#include "caffe/util/im2col.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/vision_layers.hpp"
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

namespace caffe {

template <typename Dtype>
void DeconvolutionLayer<Dtype>::compute_output_shape() {
<<<<<<< HEAD
  const int* kernel_shape_data = this->kernel_shape_.cpu_data();
  const int* stride_data = this->stride_.cpu_data();
  const int* pad_data = this->pad_.cpu_data();
  const int* dilation_data = this->dilation_.cpu_data();
  this->output_shape_.clear();
  for (int i = 0; i < this->num_spatial_axes_; ++i) {
    // i + 1 to skip channel axis
    const int input_dim = this->input_shape(i + 1);
    const int kernel_extent = dilation_data[i] * (kernel_shape_data[i] - 1) + 1;
    const int output_dim = stride_data[i] * (input_dim - 1)
        + kernel_extent - 2 * pad_data[i];
    this->output_shape_.push_back(output_dim);
  }
=======
  this->height_out_ = this->stride_h_ * (this->height_ - 1) + this->kernel_h_
      - 2 * this->pad_h_;
  this->width_out_ = this->stride_w_ * (this->width_ - 1) + this->kernel_w_
      - 2 * this->pad_w_;
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
}

template <typename Dtype>
void DeconvolutionLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top) {
  const Dtype* weight = this->blobs_[0]->cpu_data();
  for (int i = 0; i < bottom.size(); ++i) {
    const Dtype* bottom_data = bottom[i]->cpu_data();
    Dtype* top_data = top[i]->mutable_cpu_data();
    for (int n = 0; n < this->num_; ++n) {
<<<<<<< HEAD
      this->backward_cpu_gemm(bottom_data + n * this->bottom_dim_, weight,
          top_data + n * this->top_dim_);
      if (this->bias_term_) {
        const Dtype* bias = this->blobs_[1]->cpu_data();
        this->forward_cpu_bias(top_data + n * this->top_dim_, bias);
=======
      this->backward_cpu_gemm(bottom_data + bottom[i]->offset(n), weight,
          top_data + top[i]->offset(n));
      if (this->bias_term_) {
        const Dtype* bias = this->blobs_[1]->cpu_data();
        this->forward_cpu_bias(top_data + top[i]->offset(n), bias);
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
      }
    }
  }
}

template <typename Dtype>
void DeconvolutionLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
  const Dtype* weight = this->blobs_[0]->cpu_data();
  Dtype* weight_diff = this->blobs_[0]->mutable_cpu_diff();
  for (int i = 0; i < top.size(); ++i) {
    const Dtype* top_diff = top[i]->cpu_diff();
    const Dtype* bottom_data = bottom[i]->cpu_data();
    Dtype* bottom_diff = bottom[i]->mutable_cpu_diff();
    // Bias gradient, if necessary.
    if (this->bias_term_ && this->param_propagate_down_[1]) {
      Dtype* bias_diff = this->blobs_[1]->mutable_cpu_diff();
      for (int n = 0; n < this->num_; ++n) {
<<<<<<< HEAD
        this->backward_cpu_bias(bias_diff, top_diff + n * this->top_dim_);
=======
        this->backward_cpu_bias(bias_diff, top_diff + top[i]->offset(n));
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
      }
    }
    if (this->param_propagate_down_[0] || propagate_down[i]) {
      for (int n = 0; n < this->num_; ++n) {
        // Gradient w.r.t. weight. Note that we will accumulate diffs.
        if (this->param_propagate_down_[0]) {
<<<<<<< HEAD
          this->weight_cpu_gemm(top_diff + n * this->top_dim_,
              bottom_data + n * this->bottom_dim_, weight_diff);
=======
          this->weight_cpu_gemm(top_diff + top[i]->offset(n),
              bottom_data + bottom[i]->offset(n), weight_diff);
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
        }
        // Gradient w.r.t. bottom data, if necessary, reusing the column buffer
        // we might have just computed above.
        if (propagate_down[i]) {
<<<<<<< HEAD
          this->forward_cpu_gemm(top_diff + n * this->top_dim_, weight,
              bottom_diff + n * this->bottom_dim_,
=======
          this->forward_cpu_gemm(top_diff + top[i]->offset(n), weight,
              bottom_diff + bottom[i]->offset(n),
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
              this->param_propagate_down_[0]);
        }
      }
    }
  }
}

#ifdef CPU_ONLY
STUB_GPU(DeconvolutionLayer);
#endif

INSTANTIATE_CLASS(DeconvolutionLayer);
REGISTER_LAYER_CLASS(Deconvolution);

}  // namespace caffe
