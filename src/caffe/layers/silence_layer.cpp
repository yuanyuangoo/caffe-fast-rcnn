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
void SilenceLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom) {
  for (int i = 0; i < bottom.size(); ++i) {
    if (propagate_down[i]) {
      caffe_set(bottom[i]->count(), Dtype(0),
<<<<<<< HEAD
                bottom[i]->mutable_cpu_diff());
=======
                bottom[i]->mutable_cpu_data());
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
    }
  }
}

#ifdef CPU_ONLY
STUB_GPU(SilenceLayer);
#endif

INSTANTIATE_CLASS(SilenceLayer);
REGISTER_LAYER_CLASS(Silence);

}  // namespace caffe
