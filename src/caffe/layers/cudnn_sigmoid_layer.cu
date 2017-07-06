#ifdef USE_CUDNN
<<<<<<< HEAD
#include <vector>

#include "caffe/layers/cudnn_sigmoid_layer.hpp"
=======
#include <algorithm>
#include <vector>

#include "caffe/layer.hpp"
#include "caffe/vision_layers.hpp"
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

namespace caffe {

template <typename Dtype>
void CuDNNSigmoidLayer<Dtype>::Forward_gpu(const vector<Blob<Dtype>*>& bottom,
    const vector<Blob<Dtype>*>& top) {
  const Dtype* bottom_data = bottom[0]->gpu_data();
  Dtype* top_data = top[0]->mutable_gpu_data();
<<<<<<< HEAD
#if CUDNN_VERSION_MIN(5, 0, 0)
  CUDNN_CHECK(cudnnActivationForward(this->handle_,
        activ_desc_,
=======
  CUDNN_CHECK(cudnnActivationForward(this->handle_,
        CUDNN_ACTIVATION_SIGMOID,
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
        cudnn::dataType<Dtype>::one,
        this->bottom_desc_, bottom_data,
        cudnn::dataType<Dtype>::zero,
        this->top_desc_, top_data));
<<<<<<< HEAD
#else
  CUDNN_CHECK(cudnnActivationForward_v4(this->handle_,
        activ_desc_,
        cudnn::dataType<Dtype>::one,
        this->bottom_desc_, bottom_data,
        cudnn::dataType<Dtype>::zero,
        this->top_desc_, top_data));
#endif
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
}

template <typename Dtype>
void CuDNNSigmoidLayer<Dtype>::Backward_gpu(const vector<Blob<Dtype>*>& top,
    const vector<bool>& propagate_down,
    const vector<Blob<Dtype>*>& bottom) {
  if (!propagate_down[0]) {
    return;
  }

  const Dtype* top_data = top[0]->gpu_data();
  const Dtype* top_diff = top[0]->gpu_diff();
  const Dtype* bottom_data = bottom[0]->gpu_data();
  Dtype* bottom_diff = bottom[0]->mutable_gpu_diff();
<<<<<<< HEAD
#if CUDNN_VERSION_MIN(5, 0, 0)
  CUDNN_CHECK(cudnnActivationBackward(this->handle_,
        activ_desc_,
=======
  CUDNN_CHECK(cudnnActivationBackward(this->handle_,
        CUDNN_ACTIVATION_SIGMOID,
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
        cudnn::dataType<Dtype>::one,
        this->top_desc_, top_data, this->top_desc_, top_diff,
        this->bottom_desc_, bottom_data,
        cudnn::dataType<Dtype>::zero,
        this->bottom_desc_, bottom_diff));
<<<<<<< HEAD
#else
  CUDNN_CHECK(cudnnActivationBackward_v4(this->handle_,
        activ_desc_,
        cudnn::dataType<Dtype>::one,
        this->top_desc_, top_data, this->top_desc_, top_diff,
        this->bottom_desc_, bottom_data,
        cudnn::dataType<Dtype>::zero,
        this->bottom_desc_, bottom_diff));
#endif
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
}

INSTANTIATE_LAYER_GPU_FUNCS(CuDNNSigmoidLayer);

}  // namespace caffe
#endif
