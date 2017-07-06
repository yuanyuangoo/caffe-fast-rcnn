---
<<<<<<< HEAD
title: "Installation: Ubuntu"
=======
title: Installation: Ubuntu
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
---

# Ubuntu Installation

**General dependencies**

    sudo apt-get install libprotobuf-dev libleveldb-dev libsnappy-dev libopencv-dev libhdf5-serial-dev protobuf-compiler
    sudo apt-get install --no-install-recommends libboost-all-dev

<<<<<<< HEAD
**CUDA**: Install by `apt-get` or the NVIDIA `.run` package.
The NVIDIA package tends to follow more recent library and driver versions, but the installation is more manual.
If installing from packages, install the library and latest driver separately; the driver bundled with the library is usually out-of-date.
This can be skipped for CPU-only installation.

**BLAS**: install ATLAS by `sudo apt-get install libatlas-base-dev` or install OpenBLAS by `sudo apt-get install libopenblas-dev` or MKL for better CPU performance.

**Python** (optional): if you use the default Python you will need to `sudo apt-get install` the `python-dev` package to have the Python headers for building the pycaffe interface.

**Compatibility notes, 16.04**

CUDA 8 is required on Ubuntu 16.04.

=======
**CUDA**: Install via the NVIDIA package instead of `apt-get` to be certain of the library and driver versions.
Install the library and latest driver separately; the driver bundled with the library is usually out-of-date.
This can be skipped for CPU-only installation.

**BLAS**: install ATLAS by `sudo apt-get install libatlas-base-dev` or install OpenBLAS or MKL for better CPU performance.

**Python** (optional): if you use the default Python you will need to `sudo apt-get install` the `python-dev` package to have the Python headers for building the pycaffe interface.

>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
**Remaining dependencies, 14.04**

Everything is packaged in 14.04.

    sudo apt-get install libgflags-dev libgoogle-glog-dev liblmdb-dev

**Remaining dependencies, 12.04**

These dependencies need manual installation in 12.04.

    # glog
<<<<<<< HEAD
    wget https://github.com/google/glog/archive/v0.3.3.tar.gz
    tar zxvf v0.3.3.tar.gz
=======
    wget https://google-glog.googlecode.com/files/glog-0.3.3.tar.gz
    tar zxvf glog-0.3.3.tar.gz
>>>>>>> 28a579eaf0668850705598b3075b8969f22226d9
    cd glog-0.3.3
    ./configure
    make && make install
    # gflags
    wget https://github.com/schuhschuh/gflags/archive/master.zip
    unzip master.zip
    cd gflags-master
    mkdir build && cd build
    export CXXFLAGS="-fPIC" && cmake .. && make VERBOSE=1
    make && make install
    # lmdb
    git clone https://github.com/LMDB/lmdb
    cd lmdb/libraries/liblmdb
    make && make install

Note that glog does not compile with the most recent gflags version (2.1), so before that is resolved you will need to build with glog first.

Continue with [compilation](installation.html#compilation).
