git submodule init
git submodule update
cd lib/bonefish
git submodule init
git submodule update
cd ../boost
./bootstrap.sh --with-toolset=gcc --with-libraries=system,thread,program_options
./b2 -j 4