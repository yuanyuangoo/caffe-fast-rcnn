#!/usr/bin/env sh
<<<<<<< HEAD
set -e

./build/tools/caffe train \
  --solver=examples/mnist/mnist_autoencoder_solver.prototxt $@
=======

./build/tools/caffe train \
  --solver=examples/mnist/mnist_autoencoder_solver.prototxt
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
