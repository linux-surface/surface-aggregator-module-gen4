MODULE_NAME := "surface_sam"
MODULE_VERSION := "0.1"

KVERSION := "$(shell uname -r)"

obj-m += surface_sam.o

sources := Makefile
sources += dkms.conf
sources += surface_sam.c

ccflags-y := -DDEBUG

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean

dkms-install: $(sources)
	mkdir -p /usr/src/$(MODULE_NAME)-$(MODULE_VERSION)/
	cp -t /usr/src/$(MODULE_NAME)-$(MODULE_VERSION)/ $(sources)
	dkms add $(MODULE_NAME)/$(MODULE_VERSION)
	dkms build $(MODULE_NAME)/$(MODULE_VERSION)
	dkms install $(MODULE_NAME)/$(MODULE_VERSION)

dkms-uninstall:
	modprobe -r $(MODULE_NAME) || true
	dkms uninstall $(MODULE_NAME)/$(MODULE_VERSION) || true
	dkms remove $(MODULE_NAME)/$(MODULE_VERSION) --all || true
	rm -rf /usr/src/$(MODULE_NAME)-$(MODULE_VERSION)/