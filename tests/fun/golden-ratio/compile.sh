#!/bin/bash

set -xe
# i know it looks ugly but whatever
# output is [golden_ratio.exe]
gcc -o golden_ratio.exe golden_ratio.c ../../../src/brz/* ../../../src/random-cross-platform/random_interface.c -I../../../include/ -lm 


