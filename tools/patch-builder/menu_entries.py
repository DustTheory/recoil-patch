import ctypes

class MsgMapEntry(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("nMessage", ctypes.c_uint32),
        ("nCode",    ctypes.c_uint32),
        ("nId",      ctypes.c_uint32),
        ("nLastId",  ctypes.c_uint32),
        ("nSig",     ctypes.c_uint32),
        ("pfn",      ctypes.c_uint32),
    ]

assert ctypes.sizeof(MsgMapEntry) == 24

MSG_MAP_VA = 0x004D0C10
MSG_MAP_SIZE = 0x510
MSG_MAP_POINTER_VA = 0x004D0C0C

# Gets the existing launcher menu entries from the original binary
def getExistingMsgMapEntries(binary):
    entry_size = ctypes.sizeof(MsgMapEntry)
    entriesBytes = bytearray(
        binary.get_content_from_virtual_address(MSG_MAP_VA, MSG_MAP_SIZE - entry_size)
    )
    entries = [
        MsgMapEntry.from_buffer(entriesBytes, i)
        for i in range(0, len(entriesBytes), entry_size)
    ]
    return entriesBytes, entries
