#!/usr/bin/env bash
git submodule init
git submodule update

cd lib/boost
./bootstrap.sh --with-toolset=gcc --with-libraries=serialization,regex,system,thread,program_options
./b2 -j 4
cd ../bonefish
git submodule init
git submodule update
rm -r build
mkdir build
cd build
cmake .. -DBOOST_ROOT=../boost/


