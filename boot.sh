#!/usr/bin/env bash
git submodule init
git submodule update
cd lib/bonefish
git submodule init
git submodule update
rm -r build
mkdir build
cd build
cmake .. -DBOOST_ROOT=../boost/
cd ../../boost
./bootstrap.sh --with-toolset=gcc --with-libraries=system,thread,program_options
./b2 -j 4