#!/usr/bin/env sh
<<<<<<< HEAD
set -e

TOOLS=./build/tools

$TOOLS/caffe train --solver=examples/siamese/mnist_siamese_solver.prototxt $@
=======

TOOLS=./build/tools

$TOOLS/caffe train --solver=examples/siamese/mnist_siamese_solver.prototxt
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
