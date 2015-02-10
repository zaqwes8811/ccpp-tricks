#!/bin/bash
cd ~/big-3rdparty/boost_1_57_0
./bjam -d2 \
--debug-configuration \
target-os=linux \
'-sBUILD=release static multi/single' \
link=static \
--prefix= \
--layout=system \
--with-thread \
--build-dir=build_x64 \
--stagedir=stage_x64

# --toolset=gcc-4.6 \
# just gcc not work seecs
# \
#-arm_4_7 \
# Without it link correct - DANGER! maybe
#cxxflags="-O2 -mcpu=arm926ej-s -march=armv5te" \
#cflags="-O2 -mcpu=arm926ej-s -march=armv5te" \
# compileflags="" \
