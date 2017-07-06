#!/usr/bin/env sh
<<<<<<< HEAD
set -e

./build/tools/caffe train \
    --solver=examples/mnist/lenet_solver_rmsprop.prototxt $@
=======

./build/tools/caffe train --solver=examples/mnist/lenet_solver_rmsprop.prototxt
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
