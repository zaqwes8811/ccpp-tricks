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
 # http://www.linuxquestions.org/questions/debian-26/how-to-properly-install-kernel-source-in-debian-159252/
 
 ifneq (${KERNELRELEASE},)
	obj-m := old.d
	
else
	KERNEL_SOURCE := /usr/src/linux-source-3.2
	# ~/src/linux-source-3.2
	# /usr/src/linux
	PWD := $(shell pwd)
default:
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} modules
	
clean:
	${MAKE} -C ${KERNEL_SOURCE} SUBDIRS=${PWD} clean
endif
