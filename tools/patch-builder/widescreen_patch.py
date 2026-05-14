import ctypes
import struct

import lief

from menu_entries import MSG_MAP_POINTER_VA, MsgMapEntry, getExistingMsgMapEntries
from utils.patch_linker import (
    PATCH_BIN,
    getPatchSymbols,
    linkPatchObject,
    resolveFunSymbols,
)

# Resolution menu item click handlers to be patched in
# MSGMAP nId -> patch.c handler function
RESOLUTION_HANDLERS = {
    0x206:      "handle320x200ResolutionSelected",
    0x207:      "handle320x240ResolutionSelected",
    0x208:      "handle640x400ResolutionSelected",
    0x209:      "handle640x480ResolutionSelected",
    0x9C71:     "handle800x600ResolutionSelected",
    0x210:      "handle1024x768ResolutionSelected",
    0x211:      "handle1280x720ResolutionSelected",
    0x212:      "handle1280x800ResolutionSelected",
    0x213:      "handle1600x900ResolutionSelected",
    0x214:      "handle1920x1080ResolutionSelected",
    0x215:      "handle2560x1440ResolutionSelected",
    0x216:      "handle3840x2160ResolutionSelected",
}


# Resolution menu item click handlers to be patched in
# MSGMAP nId -> patch.c handler function
# Unlike RESOLUTION_HANDLERS we only need to do this for new menu entries
RESOLUTION_UPDATE_HANDLERS = {
    0x211: "handle1280x720ResolutionUpdate",
    0x212: "handle1280x800ResolutionUpdate",
    0x213: "handle1600x900ResolutionUpdate",
    0x214: "handle1920x1080ResolutionUpdate",
    0x215: "handle2560x1440ResolutionUpdate",
    0x216: "handle3840x2160ResolutionUpdate",
}

# When functioned is entered, insert JMP instruction to replacement function
FUNCTION_ENTRY_HOOKS = {
    0x004A7990: "setVideoModeParams",
}

# Replace function address directly in CALL instruction
CALL_REL32_PATCHES = {
    0x004B9911: "zeroMenuOffsetsAndCallA6840",
}

LOAD_IMAGE_VA = 0x0046dd30

def applyWidescreenPatch(binary):
    symbols = addPatchCodeSection(binary)
    addPatchResourcesSection(binary, symbols)
    patchFunctionEntries(binary, symbols)
    patchCallSites(binary, symbols)
    patchImageOverride(binary, symbols)

def patchFunctionEntries(binary, patchCodeSymbols):
    for source_addr, name in FUNCTION_ENTRY_HOOKS.items():
        target_addr = patchCodeSymbols[name]
        rel32 = (target_addr - (source_addr + 5)) & 0xFFFFFFFF
        jmp_bytes = [0xE9] + list(rel32.to_bytes(4, "little"))
        print(f"  hook entry at {source_addr:#x} -> JMP {target_addr:#x} ({name})")
        binary.patch_address(source_addr, jmp_bytes)


def patchCallSites(binary, patchCodeSymbols):
    for call_addr, name in CALL_REL32_PATCHES.items():
        target_addr = patchCodeSymbols[name]
        rel32 = (target_addr - (call_addr + 5)) & 0xFFFFFFFF
        print(f"  patch CALL at {call_addr:#x} -> {target_addr:#x} ({name})")
        binary.patch_address(call_addr + 1, list(rel32.to_bytes(4, "little")))

def patchImageOverride(binary, symbols):
    target = symbols["loadImageOverride"]
    patched = 0

    base = binary.optional_header.imagebase
    text = next(s for s in binary.sections if s.name == ".text")
    data = bytearray(text.content)
    text_va = base + text.virtual_address

    for i in range(len(data) - 4):
        if data[i] != 0xE8:
            continue
        rel32 = struct.unpack_from("<i", data, i + 1)[0]
        call_target = (text_va + i + 5 + rel32) & 0xFFFFFFFF
        if call_target != LOAD_IMAGE_VA:
            continue
        new_rel32 = (target - (text_va + i + 5)) & 0xFFFFFFFF
        binary.patch_address(text_va + i + 1, list(struct.pack("<I", new_rel32)))
        print(f"  patched loadImage call at {text_va + i:#x} -> loadImageOverride ({target:#x})")
        patched += 1

    if patched == 0:
        print("  WARNING: no loadImage call sites found")
    else:
        print(f"  patched {patched} call site(s)")

# Adds a new code section and link patch.c code
def addPatchCodeSection(binary):
    defsyms = resolveFunSymbols()

    size = linkPatchObject(text_addr=0, defsyms=defsyms)

    new_section = lief.PE.Section(".patchtext")
    new_section.content = [0] * size
    new_section.characteristics = (
        lief.PE.Section.CHARACTERISTICS.MEM_READ |
        lief.PE.Section.CHARACTERISTICS.MEM_EXECUTE |
        lief.PE.Section.CHARACTERISTICS.CNT_CODE
    )
    added_section = binary.add_section(new_section)

    absolute_addr = binary.optional_header.imagebase + added_section.virtual_address
    final_size = linkPatchObject(text_addr=absolute_addr, defsyms=defsyms)
    assert final_size == size, f"blob size changed between link passes ({size} -> {final_size})"

    added_section.content = list(PATCH_BIN.read_bytes())
    print(f".patchtext at {absolute_addr:#x} ({size} bytes)")

    return getPatchSymbols()

# Add new resources section with modified copies of data from original binary
# The modified copies will contain patched in data and function pointers
# to code inserted via addPatchCodeSection
def addPatchResourcesSection(binary, patchCodeSymbols):
    entriesBytes, entries = getExistingMsgMapEntries(binary)

    patched_ids = set()
    for entry in entries:
        if entry.nMessage != 0x111 or entry.nCode != 0:
            continue
        handler = RESOLUTION_HANDLERS.get(entry.nId)
        if handler is None:
            continue
        new_pfn = patchCodeSymbols[handler]
        print(f"  patching nId={entry.nId:#x}: pfn {entry.pfn:#x} -> {new_pfn:#x} ({handler})")
        entry.pfn = new_pfn
        patched_ids.add(entry.nId)

    missing = [nId for nId in RESOLUTION_HANDLERS if nId not in patched_ids]
    entriesBytes = appendMsgMapEntries(
        entriesBytes, missing, RESOLUTION_UPDATE_HANDLERS, patchCodeSymbols
    )

    new_section = lief.PE.Section(".patchrsrc")
    new_section.content = list(entriesBytes)
    new_section.characteristics = (
        lief.PE.Section.CHARACTERISTICS.MEM_READ |
        lief.PE.Section.CHARACTERISTICS.CNT_INITIALIZED_DATA
    )

    added_section = binary.add_section(new_section)
    absolute_addr = binary.optional_header.imagebase + added_section.virtual_address
    binary.patch_address(MSG_MAP_POINTER_VA, absolute_addr)

def appendMsgMapEntries(entriesBytes, nIds, updateHandlers, patchCodeSymbols):
    entriesBytes = bytes(entriesBytes)

    for nId in nIds:
        handler = RESOLUTION_HANDLERS[nId]
        new_pfn = patchCodeSymbols[handler]
        entry = MsgMapEntry(
            nMessage=0x111, nCode=0, nId=nId, nLastId=nId, nSig=0xC, pfn=new_pfn,
        )
        print(f"  adding ON_COMMAND nId={nId:#x}: pfn={new_pfn:#x} ({handler})")
        entriesBytes += bytes(entry)

    for nId, handler in updateHandlers.items():
        new_pfn = patchCodeSymbols[handler]
        entry = MsgMapEntry(
            nMessage=0x111, nCode=0xFFFFFFFF, nId=nId, nLastId=nId, nSig=0x2C, pfn=new_pfn,
        )
        print(f"  adding ON_UPDATE   nId={nId:#x}: pfn={new_pfn:#x} ({handler})")
        entriesBytes += bytes(entry)

    entriesBytes += bytes(ctypes.sizeof(MsgMapEntry))  # sentinel
    return entriesBytes
