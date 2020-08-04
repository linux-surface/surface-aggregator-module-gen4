# SPDX-License-Identifier: GPL-2.0-or-later
MODULE_NAME := "sb1_dgpu_sw"
MODULE_VERSION := "0.1"

KVERSION := "$(shell uname -r)"

sources := Makefile
sources += Kbuild
sources += dkms.conf
sources += sb1_dgpu_sw.c

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
