#!/bin/bash
source ../.env
cd $RECOIL_DIR
WINEPREFIX=$WINEPREFIX winedbg RECOIL.dat
