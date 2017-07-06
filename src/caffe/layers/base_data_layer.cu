#include <vector>

<<<<<<< HEAD
#include "caffe/layers/base_data_layer.hpp"
=======
#include "caffe/data_layers.hpp"
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

namespace caffe {

template <typename Dtype>
void BasePrefetchingDataLayer<Dtype>::Forward_gpu(
    const vector<Blob<Dtype>*>& bottom, const vector<Blob<Dtype>*>& top) {
<<<<<<< HEAD
  if (prefetch_current_) {
    prefetch_free_.push(prefetch_current_);
  }
  prefetch_current_ = prefetch_full_.pop("Waiting for data");
  // Reshape to loaded data.
  top[0]->ReshapeLike(prefetch_current_->data_);
  top[0]->set_gpu_data(prefetch_current_->data_.mutable_gpu_data());
  if (this->output_labels_) {
    // Reshape to loaded labels.
    top[1]->ReshapeLike(prefetch_current_->label_);
    top[1]->set_gpu_data(prefetch_current_->label_.mutable_gpu_data());
  }
=======
  // First, join the thread
  JoinPrefetchThread();
  // Reshape to loaded data.
  top[0]->ReshapeLike(this->prefetch_data_);
  // Copy the data
  caffe_copy(prefetch_data_.count(), prefetch_data_.cpu_data(),
      top[0]->mutable_gpu_data());
  if (this->output_labels_) {
    // Reshape to loaded labels.
    top[1]->ReshapeLike(prefetch_label_);
    // Copy the labels.
    caffe_copy(prefetch_label_.count(), prefetch_label_.cpu_data(),
        top[1]->mutable_gpu_data());
  }
  // Start a new prefetch thread
  CreatePrefetchThread();
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
}

INSTANTIATE_LAYER_GPU_FORWARD(BasePrefetchingDataLayer);

}  // namespace caffe
