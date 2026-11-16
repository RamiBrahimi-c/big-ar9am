#!/bin/bash

set -xe
# i know it looks ugly but whatever
# output is [pi.exe]
gcc -o pi.exe pi.c ../../../src/brz/* ../../../src/random-cross-platform/random_interface.c -I../../../include/ -lm 


