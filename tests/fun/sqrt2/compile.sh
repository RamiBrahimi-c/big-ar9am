#!/bin/bash

set -xe
# i know it looks ugly but whatever
# output is [sqrt_2.exe]
gcc -o sqrt_2.exe sqrt_2.c ../../../src/brz/* ../../../src/random-cross-platform/random_interface.c -I../../../include/ -lm 


