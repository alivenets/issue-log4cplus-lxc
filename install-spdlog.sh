#!/bin/sh

rm -rf lxc
git clone https://github.com/gabime/spdlog
cd spdlog
git checkout v1.7.0
mkdir build
cd build
cmake .. -DSPDLOG_BUILD_SHARED=ON

make -j4 && sudo make install
