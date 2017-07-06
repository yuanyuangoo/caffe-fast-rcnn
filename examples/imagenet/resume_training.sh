#!/usr/bin/env sh
<<<<<<< HEAD
set -e

./build/tools/caffe train \
    --solver=models/bvlc_reference_caffenet/solver.prototxt \
    --snapshot=models/bvlc_reference_caffenet/caffenet_train_10000.solverstate.h5 \
    $@
=======

./build/tools/caffe train \
    --solver=models/bvlc_reference_caffenet/solver.prototxt \
    --snapshot=models/bvlc_reference_caffenet/caffenet_train_10000.solverstate.h5
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
