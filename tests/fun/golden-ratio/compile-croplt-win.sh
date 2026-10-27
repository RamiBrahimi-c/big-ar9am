#!/bin/bash


# NOTE this is a proof like for cross compiling and the target here is windows 



set -xe
# i know it looks ugly but whatever
# output is [golden_ratio-win.exe]
# whish is : 
#
#   $ file golden_ratio-win.exe 
#   golden_ratio-win.exe: PE32+ executable (console) x86-64, for MS Windows, 19 sections
#

/usr/bin/x86_64-w64-mingw32-gcc -o golden_ratio-win.exe golden_ratio.c ../../../src/brz/* ../../../src/random-cross-platform/random_interface.c -I../../../include/ -lm -lbcrypt

