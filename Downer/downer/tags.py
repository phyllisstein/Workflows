import alp
from Foundation import *
from Constants import *
from ctypes import *
libc = cdll.LoadLibrary("libc.dylib")

def get_tags(path):
    path = path.encode("utf-8")
    data = create_string_buffer(kMaxDataSize)

    tags = []
    for tag in TAG_KEYS:
        name = tag.encode("utf-8")
        datasize = libc.getxattr(path, name, data, kMaxDataSize, 0, XATTR_NOFOLLOW)

        if datasize > 0:
            nsd = NSData.dataWithBytes_length_(data, datasize)
        else:
            continue

        (outObject, _, errorString) = NSPropertyListSerialization.propertyListWithData_options_format_error_(nsd,
            kCFPropertyListImmutable, None, None)
        if errorString:
            continue
        else:
            for t in outObject:
                if not t in tags:
                    tags.append(t)

    if len(tags):
        return ", ".join(tags)
    else:
        return "None"

def set_tags(tags, path):
    path = path.encode("utf-8")
    path = c_char_p(path)
    if len(tags):
        encoded_tags = NSMutableArray.arrayWithCapacity_(len(tags))
        for tag in tags:
            encoded_tags.addObject_(NSString.stringWithCString_encoding_(tag.encode("utf-8"), NSUTF8StringEncoding))

        (dataToSend, errorString) = NSPropertyListSerialization.dataWithPropertyList_format_options_error_(encoded_tags,
            kCFPropertyListBinaryFormat_v1_0, NSPropertyListImmutable, None)
        if errorString:
            alp.log("Error: {0}".format(errorString))
            return

        if dataToSend:
                bytes = c_char_p(dataToSend.bytes().tobytes())
        else:
            return "No dataToSend."

        for key in TAG_KEYS:
            keyName = key.encode("utf-8")
            check = libc.setxattr(path, keyName, bytes, dataToSend.length(), 0, XATTR_NOFOLLOW)
    else:
        for key in TAG_KEYS:
            keyName = key.encode("utf-8")
            check = libc.removexattr(path, keyName, XATTR_NOFOLLOW)
            if check != 0:
                return check

    return 0
