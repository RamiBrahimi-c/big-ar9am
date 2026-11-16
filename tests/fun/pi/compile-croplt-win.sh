#!/bin/bash


# NOTE this is a proof like for cross compiling and the target here is windows 



set -xe
# i know it looks ugly but whatever
# output is [pi-win.exe]
# whish is : 
#
#   $ file pi-win.exe 
#   pi-win.exe: PE32+ executable (console) x86-64, for MS Windows, 19 sections
#   


/usr/bin/x86_64-w64-mingw32-gcc -o pi-win.exe pi.c ../../../src/brz/* ../../../src/random-cross-platform/random_interface.c -I../../../include/ -lm -lbcrypt

