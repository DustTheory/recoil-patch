import re
import subprocess
from pathlib import Path

# Not worth straining your pretty eyes with this code <3

PATCH_OBJ = Path(__file__).resolve().parents[3] / "build" / "patch.o"
PATCH_OBJ_MERGED = PATCH_OBJ.with_suffix(".merged.o")
PATCH_ELF = PATCH_OBJ.with_suffix(".elf")
PATCH_BIN = PATCH_OBJ.with_suffix(".bin")
LD = "i686-w64-mingw32-ld"
NM = "i686-w64-mingw32-nm"
OBJCOPY = "i686-w64-mingw32-objcopy"

def resolveFunSymbols():
    nm_out = subprocess.check_output([NM, "--undefined-only", str(PATCH_OBJ)], text=True)
    defsyms = []
    for line in nm_out.splitlines():
        parts = line.split()
        if not parts:
            continue
        sym = parts[-1]
        m = re.match(r"^[@_]?(?:FUN|DAT)_([0-9a-fA-F]+)(?:@\d+)?$", sym)
        if m:
            defsyms.append(f"--defsym={sym}=0x{m.group(1)}")
    return defsyms


def linkPatchObject(text_addr, defsyms):
    subprocess.run(
        [OBJCOPY, "--rename-section", ".rdata=.text",
         str(PATCH_OBJ), str(PATCH_OBJ_MERGED)],
        check=True,
    )
    subprocess.run(
        [LD, f"-Ttext={text_addr:#x}",
         *defsyms, "-o", str(PATCH_ELF), str(PATCH_OBJ_MERGED)],
        check=True,
    )
    subprocess.run(
        [OBJCOPY, "-O", "binary", "--only-section=.text",
         str(PATCH_ELF), str(PATCH_BIN)],
        check=True,
    )
    return PATCH_BIN.stat().st_size


def getPatchSymbols():
    nm_out = subprocess.check_output([NM, "--defined-only", str(PATCH_ELF)], text=True)
    symbols = {}
    for line in nm_out.splitlines():
        parts = line.split()
        if len(parts) < 3:
            continue
        addr_hex, sym_type, sym = parts[0], parts[1], parts[-1]
        if sym_type not in ("T", "t"):
            continue
        symbols[sym.lstrip("_")] = int(addr_hex, 16)
    return symbols
