#!/bin/sh

# https://code.google.com/p/v8/wiki/CrossCompilingForARM

V=/home/zaqwes/big_device/codesourcery/arm-2009q1

export TOOL_PREFIX=$V/bin/arm-none-linux-gnueabi
export CXX=$TOOL_PREFIX-g++
export AR=$TOOL_PREFIX-ar
export RANLIB=$TOOL_PREFIX-ranlib
export CC=$TOOL_PREFIX-gcc
export LD=$TOOL_PREFIX-g++

#export CCFLAGS="-march=armv7-a -mtune=cortex-a8 -mfpu=vfp"
export CCFLAGS="-mcpu=arm926ej-s -march=armv5te"
export ARM_TARGET_LIB=$V/arm-none-linux-gnueabi/libc

make arm.release wordsize=32 snapshot=off sample=shell werror=no armfloatabi=softfp
