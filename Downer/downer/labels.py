import struct
from Constants import *
from ctypes import *
libc = cdll.LoadLibrary("libc.dylib")


def get_flags(path):
    path = path.encode("utf-8")
    data = create_string_buffer(kMaxDataSize)
    name = ATTR.encode("utf-8")

    datasize = libc.getxattr(path, name, data, kMaxDataSize, 0, XATTR_NOFOLLOW)
    if datasize < 0:
        return None
    else:
        data_bytes = string_at(addressof(data), datasize)
        flags = struct.unpack(32*'B', data_bytes)
        return flags

def get_finder_label(path):
    flags = get_flags(path)
    if flags:
        color = flags[9] >> 1 & 7
    else:
        color = 0
    return COLORS[color]

def set_finder_label(path, color):
    s_color = color << 1

    flags = get_flags(path)
    if flags:
        flags = list(flags)
        flags[9] = s_color
        flags = tuple(flags)
    else:
        flags = []
        for i in range(32):
            flags.append(0)
        flags[9] = s_color
        flags = tuple(flags)

    path = path.encode("utf-8")
    data = create_string_buffer(32)
    data.raw = struct.pack(32*'B', *flags)
    name = ATTR.encode("utf-8")

    err = libc.setxattr(path, name, data, sizeof(data), 0, XATTR_NOFOLLOW)
    if err < 0:
        raise Exception("Failed to set label color for {0}".format(path.decode("utf-8")))
