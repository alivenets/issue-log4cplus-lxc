#!/bin/bash -e

rm -rf log4cplus
git clone https://github.com/log4cplus/log4cplus.git
mkdir log4cplus/build
cd log4cplus/build
git checkout REL_2_0_1
git submodule update --init
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make install
