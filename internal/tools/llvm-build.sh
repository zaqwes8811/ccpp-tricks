#!/bin/bash
export root=$HOME/toolchains_gcc482_clang
export CC=$root/bin/gcc CXX=$root/bin/g++ 

cmake .. \
	-DCMAKE_CXX_LINK_FLAGS="-Wl,-rpath,$root/lib64 -L$root/lib64" \
	-DCMAKE_INSTALL_PREFIX:PATH=$root

# not work in Ubuntu14.04/x64/gcc4.8.2
# user configure
