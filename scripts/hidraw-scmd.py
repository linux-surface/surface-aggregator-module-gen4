#!/usr/bin/env python3
import fcntl
import ctypes
import os
import sys


IOC_NRBITS = 8
IOC_TYPEBITS = 8
IOC_SIZEBITS = 14
IOC_DIRBITS = 2

IOC_NRSHIFT = 0
IOC_TYPESHIFT = IOC_NRSHIFT + IOC_NRBITS
IOC_SIZESHIFT = IOC_TYPESHIFT + IOC_TYPEBITS
IOC_DIRSHIFT = IOC_SIZESHIFT + IOC_SIZEBITS

IOC_NONE = 0
IOC_WRITE = 1
IOC_READ = 2


def IOC(dir, type, nr, size):
    """Linux _IOC macro as function."""
    return (((dir) << IOC_DIRSHIFT) |
            ((type) << IOC_TYPESHIFT) |
            ((nr) << IOC_NRSHIFT) |
            ((size) << IOC_SIZESHIFT))


def IOWR(type, nr, size):
    """Linux _IOWR macro as function."""
    return IOC(IOC_WRITE | IOC_READ, type, nr, size)


HIDIOCSFEATURE = lambda len: IOWR(ord('H'), 0x06, len)
HIDIOCGFEATURE = lambda len: IOWR(ord('H'), 0x07, len)


class HidDevice():
    def __init__(self, fd):
        self.fd = fd

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close()

    @staticmethod
    def open(path):
        return HidDevice(os.open(path, os.O_RDWR))

    def close(self):
        os.close(self.fd)

    def _ioctl(self, *args, **kwargs):
        result = fcntl.ioctl(self.fd, *args, **kwargs)

        if result < 0:
            raise IOError(result)

        return result

    def setFeatureReport(self, report):
        buf = (ctypes.c_char * len(report)).from_buffer(bytearray(report))
        self._ioctl(HIDIOCSFEATURE(len(report)), buf, True)

    def scmd(self, code):
        data = [
            0x24,    # first byte must be report id
            0x24, code, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        ]

        self.setFeatureReport(bytes(data))


def main():
    with HidDevice.open(sys.argv[1]) as dev:
        dev.scmd(int(sys.argv[2], 0))


if __name__ == '__main__':
    main()
