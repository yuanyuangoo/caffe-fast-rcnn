#!/usr/bin/env sh
# This script converts the cifar data into leveldb format.
<<<<<<< HEAD
set -e
=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9

EXAMPLE=examples/cifar10
DATA=data/cifar10
DBTYPE=lmdb

echo "Creating $DBTYPE..."

rm -rf $EXAMPLE/cifar10_train_$DBTYPE $EXAMPLE/cifar10_test_$DBTYPE

./build/examples/cifar10/convert_cifar_data.bin $DATA $EXAMPLE $DBTYPE

echo "Computing image mean..."

./build/tools/compute_image_mean -backend=$DBTYPE \
  $EXAMPLE/cifar10_train_$DBTYPE $EXAMPLE/mean.binaryproto

echo "Done."
