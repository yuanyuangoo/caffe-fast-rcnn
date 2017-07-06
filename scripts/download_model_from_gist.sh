#!/usr/bin/env sh

GIST=$1
DIRNAME=${2:-./models}

if [ -z $GIST ]; then
  echo "usage: download_model_from_gist.sh <gist_id> <dirname>"
  exit
fi

GIST_DIR=$(echo $GIST | tr '/' '-')
MODEL_DIR="$DIRNAME/$GIST_DIR"

if [ -d $MODEL_DIR ]; then
    echo "$MODEL_DIR already exists! Please make sure you're not overwriting anything important!"
    exit
fi

echo "Downloading Caffe model info to $MODEL_DIR ..."
mkdir -p $MODEL_DIR
<<<<<<< HEAD
wget https://gist.github.com/$GIST/download -O $MODEL_DIR/gist.zip
unzip -j $MODEL_DIR/gist.zip -d $MODEL_DIR
rm $MODEL_DIR/gist.zip
=======
wget https://gist.github.com/$GIST/download -O $MODEL_DIR/gist.tar.gz
tar xzf $MODEL_DIR/gist.tar.gz --directory=$MODEL_DIR --strip-components=1
rm $MODEL_DIR/gist.tar.gz
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
echo "Done"
