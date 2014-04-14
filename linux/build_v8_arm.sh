#!/bin/sh

# https://code.google.com/p/v8/wiki/CrossCompilingForARM

V=/home/zaqwes/big_device/condesourcery/arm-2009q1

export TOOL_PREFIX=$V/bin/arm-none-linux-gnueabi
export CXX=$TOOL_PREFIX-g++
export AR=$TOOL_PREFIX-ar
export RANLIB=$TOOL_PREFIX-ranlib
export CC=$TOOL_PREFIX-gcc
export LD=$TOOL_PREFIX-g++

#export CCFLAGS="-march=armv7-a -mtune=cortex-a8 -mfpu=vfp"
export CCFLAGS="-mcpu=arm926ej-s -march=armv5te -mno-thumb-interwork"
export ARM_TARGET_LIB=$V/arm-none-linux-gnueabi/libc

# http://www.wigwag.com/devblog/cross-compile-v8-target-arm/!!
# https://code.google.com/p/v8/wiki/CrossCompilingForARM
# -j4 - ?
make arm.debug wordsize=32 snapshot=off sample=shell vfp3=off werror=no armfloatabi=soft armv7=false hardfp=off armthumb=off OUTDIR=./armv5te_dbg_out_armfloat_soft_off_some
# off max count values
# wordsize=32 snapshot=off arch=arm vfp3=off armeabi=soft sample=shell
# armeabi=soft
#fp
#
# Try arm.debug
# GCC switches: -march=XXX, -mtune=XXX, -mno-thumb-interwork
# V8 scons options: vfp3=off/on, armeabi=off/on
# V8 scons snapshot=off  - Later try to move to snapshot=on
