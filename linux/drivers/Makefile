# http://www.linuxdevcenter.com/pub/a/linux/2007/07/05/devhelloworld-a-simple-introduction-to-device-drivers-under-linux.html
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

obj-m := ofd.o 

# KDIR is the location of the kernel source.  The current standard is
# to link to the associated source tree from the directory containing
# the compiled modules.
KDIR  := /lib/modules/$(shell uname -r)/build

# PWD is the current working directory and the location of our module
# source files.
PWD   := $(shell pwd)

# default is the default make target.  The rule here says to run make
# with a working directory of the directory containing the kernel
# source and compile only the modules in the PWD (local) directory.
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

#ifneq (${KERNELRELEASE},)
#	obj-m := old.d
#	
#else
#	KERNEL_SOURCE := /usr/src/linux
#	# ~/src/linux-source-3.2
#	# 
#	PWD := $(shell pwd)
#default:
#	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} modules
#	
#clean:
#	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} clean
#endif
