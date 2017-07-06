#include <map>
#include <string>

<<<<<<< HEAD
#include "boost/scoped_ptr.hpp"
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
#include "gtest/gtest.h"

#include "caffe/common.hpp"
#include "caffe/layer.hpp"
#include "caffe/layer_factory.hpp"
<<<<<<< HEAD
#include "caffe/util/db.hpp"
#include "caffe/util/io.hpp"
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

#include "caffe/test/test_caffe_main.hpp"

namespace caffe {

template <typename TypeParam>
class LayerFactoryTest : public MultiDeviceTest<TypeParam> {};

TYPED_TEST_CASE(LayerFactoryTest, TestDtypesAndDevices);

TYPED_TEST(LayerFactoryTest, TestCreateLayer) {
  typedef typename TypeParam::Dtype Dtype;
  typename LayerRegistry<Dtype>::CreatorRegistry& registry =
      LayerRegistry<Dtype>::Registry();
  shared_ptr<Layer<Dtype> > layer;
<<<<<<< HEAD
=======
  LayerParameter layer_param;
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
  for (typename LayerRegistry<Dtype>::CreatorRegistry::iterator iter =
       registry.begin(); iter != registry.end(); ++iter) {
    // Special case: PythonLayer is checked by pytest
    if (iter->first == "Python") { continue; }
<<<<<<< HEAD
    LayerParameter layer_param;
    // Data layers expect a DB
    if (iter->first == "Data") {
#ifdef USE_LEVELDB
      string tmp;
      MakeTempDir(&tmp);
      boost::scoped_ptr<db::DB> db(db::GetDB(DataParameter_DB_LEVELDB));
      db->Open(tmp, db::NEW);
      db->Close();
      layer_param.mutable_data_param()->set_source(tmp);
#else
      continue;
#endif  // USE_LEVELDB
    }
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
    layer_param.set_type(iter->first);
    layer = LayerRegistry<Dtype>::CreateLayer(layer_param);
    EXPECT_EQ(iter->first, layer->type());
  }
}

}  // namespace caffe
