obj-m := sstf-iosched.o
BUILDROOT_DIR := ../buildroot
KDIR := $(BUILDROOT_DIR)/output/build/linux-master
COMPILER := $(BUILDROOT_DIR)/output/host/bin/i686-buildroot-linux-uclibc-gcc

all:
	$(MAKE) -C $(KDIR) M=$$PWD
	$(MAKE) -C $(KDIR) M=$$PWD modules_install INSTALL_MOD_PATH=../../target
	$(COMPILER) -o sector_read sector_read.c
	cp sector_read $(BUILDROOT_DIR)/output/target/bin
	
	
	
clean:
	rm -f *.o *.ko
	rm -f modules.order
	rm -f Module.symvers
	rm -f sstf-iosched.mod.c
	rm -f sector_read
