#!/bin/bash
source ../.env
cd $RECOIL_DIR
WINEPREFIX=$WINEPREFIX wine RECOIL.dat 2> ./recoil_run.log
