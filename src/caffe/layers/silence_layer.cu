#include <vector>

<<<<<<< HEAD
#include "caffe/layers/silence_layer.hpp"
=======
#include "caffe/common_layers.hpp"
#include "caffe/layer.hpp"
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
#include "caffe/util/math_functions.hpp"

namespace caffe {

template <typename Dtype>
void SilenceLayer<Dtype>::Forward_gpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top) {
  // Do nothing.
}

template <typename Dtype>
void SilenceLayer<Dtype>::Backward_gpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
  for (int i = 0; i < bottom.size(); ++i) {
    if (propagate_down[i]) {
      caffe_gpu_set(bottom[i]->count(), Dtype(0),
<<<<<<< HEAD
                    bottom[i]->mutable_gpu_diff());
=======
                    bottom[i]->mutable_gpu_data());
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
    }
  }
}

INSTANTIATE_LAYER_GPU_FUNCS(SilenceLayer);

}  // namespace caffe
