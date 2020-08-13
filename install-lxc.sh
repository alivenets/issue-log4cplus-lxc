#!/bin/sh

rm -rf lxc
git clone https://github.com/lxc/lxc
cd lxc
git checkout lxc-3.1.0
./autogen.sh
./configure --prefix=/usr --enable-capabilities
make -j4 && sudo make install
