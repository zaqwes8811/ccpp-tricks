# Tutorial:
# !!http://www.linuxdevcenter.com/pub/a/linux/2007/07/05/devhelloworld-a-simple-introduction-to-device-drivers-under-linux.html
# 
# Get kernel tree for driver comp.:
# http://linux.seindal.dk/2004/08/15/getting-a-debian-kernel-source-tree-for-driver-compilation/
#
# Install headers
# http://www.garron.me/en/go2linux/how-install-linux-kernel-headers-debian-or-ubuntu.html
#
# Install sources - vanilla way^
# http://okomestudio.net/biboroku/?p=1903
# Ways:
# http://www.linuxquestions.org/questions/debian-26/how-to-properly-install-kernel-source-in-debian-159252/

# obj-m is a list of what kernel modules to build.  The .o and other
# objects will be automatically built from the corresponding .c file -
# no need to list the source files explicitly.

# Такая сборка тоже заработала, но нужно было для Debian поставить module-assistant


# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
ifneq ($(KERNELRELEASE),)
	obj-m := hello.o
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	PWD := $(shell pwd)
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

