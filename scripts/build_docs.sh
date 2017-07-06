#!/bin/bash
# Build documentation for display in web browser.

PORT=${1:-4000}

echo "usage: build_docs.sh [port]"

# Find the docs dir, no matter where the script is called
ROOT_DIR="$( cd "$(dirname "$0")"/.. ; pwd -P )"
cd $ROOT_DIR

# Gather docs.
scripts/gather_examples.sh

<<<<<<< HEAD
# Split caffe.proto for inclusion by layer catalogue.
scripts/split_caffe_proto.py

=======
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
# Generate developer docs.
make docs

# Display docs using web server.
cd docs
jekyll serve -w -s . -d _site --port=$PORT
