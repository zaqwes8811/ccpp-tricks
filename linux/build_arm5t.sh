#!/bin/bash

# http://processors.wiki.ti.com/index.php/Building_Qt

#-no-gui \ -no-opengl \ -no-webkit \
# /home/user/arm-programming/third_party/qt-everywhere-opensource-src-4.8.5
#
# TODO: was -fno-exceptions 
#http://stackoverflow.com/questions/8802992/why-does-my-code-compile-with-fno-exceptions-in-qt-creator-when-i-try-to-use-ex
# http://qtlinux.narod.ru/qt483_problems.htm
#
# TODO: make script - wget  tar 
# cp config..
#	-qt-mouse-pc \
#	-qt-mouse-linuxtp \
#	-qt-mouse-linuxinput \
#	-plugin-mouse-linuxtp \
#	-plugin-mouse-pc \


./configure -prefix ~/big_device/third_party/Qt4.8.1_armv5te \
	-embedded arm \
	-platform qws/linux-x86-g++ \
	-xplatform qws/linux-arm5te-g++ \
	-exceptions \
	-no-webkit \
	-no-javascript-jit \
	-no-phonon \
	-no-xvideo \
	-no-multimedia \
	-no-audio-backend \
	-no-phonon-backend \
	-no-mmx \
	-no-3dnow \
	-no-sse \
	-no-sse2 \
	-no-glib \
	-no-cups \
	-no-largefile \
	-no-accessibility \
	-no-openssl \
	-no-gtkstyle \
	-fast \
	-depths 16,24,32 \
	-little-endian
