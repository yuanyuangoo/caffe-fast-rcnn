#!/usr/bin/env sh
<<<<<<< HEAD
set -e
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

TOOLS=./build/tools

$TOOLS/caffe train \
<<<<<<< HEAD
    --solver=examples/cifar10/cifar10_full_solver.prototxt $@
=======
    --solver=examples/cifar10/cifar10_full_solver.prototxt
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

# reduce learning rate by factor of 10
$TOOLS/caffe train \
    --solver=examples/cifar10/cifar10_full_solver_lr1.prototxt \
<<<<<<< HEAD
    --snapshot=examples/cifar10/cifar10_full_iter_60000.solverstate $@
=======
    --snapshot=examples/cifar10/cifar10_full_iter_60000.solverstate.h5
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

# reduce learning rate by factor of 10
$TOOLS/caffe train \
    --solver=examples/cifar10/cifar10_full_solver_lr2.prototxt \
<<<<<<< HEAD
    --snapshot=examples/cifar10/cifar10_full_iter_65000.solverstate $@
=======
    --snapshot=examples/cifar10/cifar10_full_iter_65000.solverstate.h5
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
