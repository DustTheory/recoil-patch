#!/bin/bash
source ../.env
i686-w64-mingw32-objdump -p $SYSTEM32_DIR/kernel32.dll | grep "^\s*\[\s*[0-9]*\] [A-Za-z_]" | sed 's/.*\[\s*\([0-9]*\)\] \([A-Za-z_][A-Za-z0-9_]*\).*/    \2 = real_kernel32.\2 @\1/' > kernel32.def
