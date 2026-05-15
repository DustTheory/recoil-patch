#!/bin/bash
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/../.env"
cd $RECOIL_DIR
WINEPREFIX=$WINEPREFIX WINEDLLOVERRIDES="user32=n,b" winedbg RECOIL.dat
