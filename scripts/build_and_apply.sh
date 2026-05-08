#!/bin/bash

# Builds and applies the patch

source ../.env

# Make logs directory in c drive if it does not already exist
mkdir -p $DRIVE_C_DIR/log

# Backup original executables if they don't already exist
if [ ! -f ../build/Recoil_original.exe ]; then
    cp $RECOIL_DIR/Recoil.exe ../build/Recoil_original.exe
fi
if [ ! -f ../build/Recoil_original.dat ]; then
    cp $RECOIL_DIR/RECOIL.dat ../build/Recoil_original.dat
fi

# Build user32.dll
i686-w64-mingw32-gcc -c -o ../build/user32.o ../src/user32/user32.c -I../src/user32 -I../include
i686-w64-mingw32-gcc -c -o ../build/menu.o ../src/user32/menu.c -I../src/user32 -I../include
i686-w64-mingw32-gcc -shared -o ../build/user32.dll ../build/user32.o ../build/menu.o ../src/user32/user32.def -static-libgcc

# Build patchk32.dll
i686-w64-mingw32-gcc -shared -o ../build/patchk32.dll ../src/patchk32/kernel32.c ../src/patchk32/kernel32.def -static-libgcc

# Build patch.c
i686-w64-mingw32-gcc -c -o ../build/patch.o ../src/patch/patch.c -I../include -march=i386 -mno-sse -mno-mmx -ffreestanding -fno-stack-protector -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-ident -O0 -fno-pic

# Copy original dll files to recoil directory
cp $SYSTEM32_DIR/kernel32.dll $RECOIL_DIR/real_kernel32.dll
cp $SYSTEM32_DIR/user32.dll $RECOIL_DIR/real_user32.dll

# Copy patched dll files to recoil directory
cp ../build/user32.dll $RECOIL_DIR/user32.dll
cp ../build/patchk32.dll $RECOIL_DIR/patchk32.dll

# Build patched binary
cd ../tools/patch-builder
# uv run main.py ../../build/Recoil_original.exe ../../build/Recoil.exe
uv run main.py ../../build/Recoil_original.dat ../../build/RECOIL.dat

# Copy patched binary
# cp ../../build/Recoil.exe $RECOIL_DIR/Recoil.exe
cp ../../build/RECOIL.dat $RECOIL_DIR/RECOIL.dat