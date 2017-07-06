#include "glog/logging.h"
#include "gtest/gtest.h"

#include "caffe/internal_thread.hpp"
<<<<<<< HEAD
#include "caffe/util/math_functions.hpp"
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

#include "caffe/test/test_caffe_main.hpp"

namespace caffe {


class InternalThreadTest : public ::testing::Test {};

TEST_F(InternalThreadTest, TestStartAndExit) {
  InternalThread thread;
  EXPECT_FALSE(thread.is_started());
<<<<<<< HEAD
  thread.StartInternalThread();
  EXPECT_TRUE(thread.is_started());
  thread.StopInternalThread();
  EXPECT_FALSE(thread.is_started());
}

class TestThreadA : public InternalThread {
  void InternalThreadEntry() {
    EXPECT_EQ(4244559767, caffe_rng_rand());
  }
};

class TestThreadB : public InternalThread {
  void InternalThreadEntry() {
    EXPECT_EQ(1726478280, caffe_rng_rand());
  }
};

TEST_F(InternalThreadTest, TestRandomSeed) {
  TestThreadA t1;
  Caffe::set_random_seed(9658361);
  t1.StartInternalThread();
  t1.StopInternalThread();

  TestThreadA t2;
  Caffe::set_random_seed(9658361);
  t2.StartInternalThread();
  t2.StopInternalThread();

  TestThreadB t3;
  Caffe::set_random_seed(3435563);
  t3.StartInternalThread();
  t3.StopInternalThread();
}

=======
  EXPECT_TRUE(thread.StartInternalThread());
  EXPECT_TRUE(thread.is_started());
  EXPECT_TRUE(thread.WaitForInternalThreadToExit());
  EXPECT_FALSE(thread.is_started());
}

>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
}  // namespace caffe

