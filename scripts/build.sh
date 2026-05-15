#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$SCRIPT_DIR/.."

if [ -z "$1" ]; then
    echo "Usage: build.sh <path_to_original_dat>"
    exit 1
fi
INPUT_DAT="$1"

source "$ROOT/.env"

mkdir -p "$ROOT/build"

# Build pusr32.dll
i686-w64-mingw32-gcc -c -o "$ROOT/build/user32.o" "$ROOT/src/user32/user32.c" -I"$ROOT/src/user32" -I"$ROOT/include"
i686-w64-mingw32-gcc -c -o "$ROOT/build/menu.o" "$ROOT/src/user32/menu.c" -I"$ROOT/src/user32" -I"$ROOT/include"
i686-w64-mingw32-gcc -shared -o "$ROOT/build/pusr32.dll" "$ROOT/build/user32.o" "$ROOT/build/menu.o" "$ROOT/src/user32/user32.def" -static-libgcc

# Build patch.c
i686-w64-mingw32-gcc -c -o "$ROOT/build/patch.o" "$ROOT/src/patch/patch.c" -I"$ROOT/include" -march=i386 -mno-sse -mno-mmx -ffreestanding -fno-stack-protector -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-ident -O0 -fno-pic

# Convert patch images
mkdir -p "$ROOT/build/patch-assets"
for png in "$ROOT/assets/"*.png; do
    bin="$ROOT/build/patch-assets/$(basename "${png%.png}.bin")"
    uv --directory "$ROOT/tools/patch-builder" run image_convert.py "$png" "$bin"
done

# Build patched binary
uv --directory "$ROOT/tools/patch-builder" run main.py "$INPUT_DAT" "$ROOT/build/RECOIL.dat"

# Clean up intermediary build files
rm -f "$ROOT/build/"*.o "$ROOT/build/"*.elf "$ROOT/build/"*.bin
