#!/bin/sh

# https://code.google.com/p/v8/wiki/CrossCompilingForARM

export TOOL_PREFIX=/opt/codesourcery/arm-2009q1/bin/arm-none-linux-gnueabi
#export TOOL_PREFIX=/opt/codesourcery/cross-gcc/arm-2007q1/bin/arm-none-linux-gnueabi
export CXX=$TOOL_PREFIX-g++
export AR=$TOOL_PREFIX-ar
export RANLIB=$TOOL_PREFIX-ranlib
export CC=$TOOL_PREFIX-gcc
export LD=$TOOL_PREFIX-g++
#$TOOL_PREFIX-ld

#export CCFLAGS="-march=armv7-a -mtune=cortex-a8 -mfpu=vfp"
export CCFLAGS="-mcpu=arm926ej-s -march=armv5te"
export ARM_TARGET_LIB=/opt/codesourcery/arm-2009q1/arm-none-linux-gnueabi/libc

make arm.release wordsize=32 snapshot=off sample=shell werror=no armfloatabi=softfp
