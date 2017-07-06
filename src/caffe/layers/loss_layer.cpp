<<<<<<< HEAD
#include <vector>

#include "caffe/layers/loss_layer.hpp"
=======
#include <algorithm>
#include <cfloat>
#include <cmath>
#include <vector>

#include "caffe/layer.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/math_functions.hpp"
#include "caffe/vision_layers.hpp"
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

namespace caffe {

template <typename Dtype>
void LossLayer<Dtype>::LayerSetUp(
    const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
  // LossLayers have a non-zero (1) loss by default.
  if (this->layer_param_.loss_weight_size() == 0) {
    this->layer_param_.add_loss_weight(Dtype(1));
  }
}

template <typename Dtype>
void LossLayer<Dtype>::Reshape(
    const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
<<<<<<< HEAD
  CHECK_EQ(bottom[0]->shape(0), bottom[1]->shape(0))
      << "The data and label should have the same first dimension.";
=======
  CHECK_EQ(bottom[0]->num(), bottom[1]->num())
      << "The data and label should have the same number.";
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
  vector<int> loss_shape(0);  // Loss layers output a scalar; 0 axes.
  top[0]->Reshape(loss_shape);
}

INSTANTIATE_CLASS(LossLayer);

}  // namespace caffe
