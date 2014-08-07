#!/bin/bash
V=/home/zaqwes/big_device/condesourcery/arm-2009q1/bin/arm-none-linux-gnueabi-g++

#export 
#export 
#export 
make LDFLAGS="-Wl,-R -Wl,." CFLAGS="-mcpu=arm926ej-s -march=armv5te" CC=$V
