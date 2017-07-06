// TODO (sergeyk): effect should not be dependent on phase. wasted memcpy.

#include <vector>

<<<<<<< HEAD
#include "caffe/layers/dropout_layer.hpp"
#include "caffe/util/math_functions.hpp"
=======
#include "caffe/common.hpp"
#include "caffe/layer.hpp"
#include "caffe/syncedmem.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/vision_layers.hpp"
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

namespace caffe {

template <typename Dtype>
void DropoutLayer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top) {
  NeuronLayer<Dtype>::LayerSetUp(bottom, top);
  threshold_ = this->layer_param_.dropout_param().dropout_ratio();
  DCHECK(threshold_ > 0.);
  DCHECK(threshold_ < 1.);
  scale_ = 1. / (1. - threshold_);
  uint_thres_ = static_cast<unsigned int>(UINT_MAX * threshold_);
<<<<<<< HEAD
  scale_train_ = this->layer_param_.dropout_param().scale_train();
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
}

template <typename Dtype>
void DropoutLayer<Dtype>::Reshape(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top) {
  NeuronLayer<Dtype>::Reshape(bottom, top);
  // Set up the cache for random number generation
<<<<<<< HEAD
  // ReshapeLike does not work because rand_vec_ is of Dtype uint
  rand_vec_.Reshape(bottom[0]->shape());
=======
  rand_vec_.Reshape(bottom[0]->num(), bottom[0]->channels(),
      bottom[0]->height(), bottom[0]->width());
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
}

template <typename Dtype>
void DropoutLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
    const vector<Blob<Dtype>*>& top) {
  const Dtype* bottom_data = bottom[0]->cpu_data();
  Dtype* top_data = top[0]->mutable_cpu_data();
  unsigned int* mask = rand_vec_.mutable_cpu_data();
  const int count = bottom[0]->count();
  if (this->phase_ == TRAIN) {
    // Create random numbers
    caffe_rng_bernoulli(count, 1. - threshold_, mask);
<<<<<<< HEAD
    if (scale_train_) {
      for (int i = 0; i < count; ++i) {
        top_data[i] = bottom_data[i] * mask[i] * scale_;
      }
    } else {
      for (int i = 0; i < count; ++i) {
        top_data[i] = bottom_data[i] * mask[i];
      }
    }
  } else {
    caffe_copy(bottom[0]->count(), bottom_data, top_data);
    if (!scale_train_) {
      caffe_scal<Dtype>(  count, 1. / scale_, top_data);
    }
=======
    for (int i = 0; i < count; ++i) {
      top_data[i] = bottom_data[i] * mask[i] * scale_;
    }
  } else {
    caffe_copy(bottom[0]->count(), bottom_data, top_data);
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
  }
}

template <typename Dtype>
void DropoutLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
    const vector<bool>& propagate_down,
    const vector<Blob<Dtype>*>& bottom) {
  if (propagate_down[0]) {
    const Dtype* top_diff = top[0]->cpu_diff();
    Dtype* bottom_diff = bottom[0]->mutable_cpu_diff();
    if (this->phase_ == TRAIN) {
      const unsigned int* mask = rand_vec_.cpu_data();
      const int count = bottom[0]->count();
<<<<<<< HEAD
      if (scale_train_) {
        for (int i = 0; i < count; ++i) {
          bottom_diff[i] = top_diff[i] * mask[i] * scale_;
        }
      } else {
        for (int i = 0; i < count; ++i) {
          bottom_diff[i] = top_diff[i] * mask[i];
        }
      }
    } else {
      caffe_copy(top[0]->count(), top_diff, bottom_diff);
      if (!scale_train_) {
        caffe_scal<Dtype>(top[0]->count(), 1. / scale_, bottom_diff);
      }
=======
      for (int i = 0; i < count; ++i) {
        bottom_diff[i] = top_diff[i] * mask[i] * scale_;
      }
    } else {
      caffe_copy(top[0]->count(), top_diff, bottom_diff);
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
    }
  }
}


#ifdef CPU_ONLY
STUB_GPU(DropoutLayer);
#endif

INSTANTIATE_CLASS(DropoutLayer);
REGISTER_LAYER_CLASS(Dropout);

}  // namespace caffe
