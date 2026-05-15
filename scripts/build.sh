#!/bin/bash

# Builds the patch output into the build directory

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$SCRIPT_DIR/.."

source "$ROOT/.env"

mkdir -p "$ROOT/build"

# Backup original executables if they don't already exist
if [ ! -f "$ROOT/build/Recoil_original.exe" ]; then
    cp "$RECOIL_DIR/Recoil.exe" "$ROOT/build/Recoil_original.exe"
fi
if [ ! -f "$ROOT/build/Recoil_original.dat" ]; then
    cp "$RECOIL_DIR/RECOIL.dat" "$ROOT/build/Recoil_original.dat"
fi

# Build pusr32.dll
i686-w64-mingw32-gcc -c -o "$ROOT/build/user32.o" "$ROOT/src/user32/user32.c" -I"$ROOT/src/user32" -I"$ROOT/include"
i686-w64-mingw32-gcc -c -o "$ROOT/build/menu.o" "$ROOT/src/user32/menu.c" -I"$ROOT/src/user32" -I"$ROOT/include"
i686-w64-mingw32-gcc -shared -o "$ROOT/build/pusr32.dll" "$ROOT/build/user32.o" "$ROOT/build/menu.o" "$ROOT/src/user32/user32.def" -static-libgcc

# Build patch.c
i686-w64-mingw32-gcc -c -o "$ROOT/build/patch.o" "$ROOT/src/patch/patch.c" -I"$ROOT/include" -march=i386 -mno-sse -mno-mmx -ffreestanding -fno-stack-protector -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-ident -O0 -fno-pic

# Copy system DLLs
cp "$SYSTEM32_DIR/user32.dll" "$ROOT/build/real_user32.dll"

# Copy third-party DLLs
cp "$ROOT/third-party-dlls/"* "$ROOT/build/"

# Convert patch images
mkdir -p "$ROOT/build/patch-assets"
for png in "$ROOT/assets/"*.png; do
    bin="$ROOT/build/patch-assets/$(basename "${png%.png}.bin")"
    uv --directory "$ROOT/tools/patch-builder" run image_convert.py "$png" "$bin"
done

# Build patched binary
uv --directory "$ROOT/tools/patch-builder" run main.py "$ROOT/build/Recoil_original.dat" "$ROOT/build/RECOIL.dat"
