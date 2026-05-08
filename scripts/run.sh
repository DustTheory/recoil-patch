#!/bin/bash
source ../.env
cd $RECOIL_DIR
WINEPREFIX=$WINEPREFIX WINEDLLOVERRIDES="shell32=n,b;kernel32=n,b;user32=n,b" wine RECOIL.dat 2> ./recoil_run.log
