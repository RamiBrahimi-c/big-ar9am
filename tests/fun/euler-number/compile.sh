#!/bin/bash

set -xe
# i know it looks ugly but whatever
# output is [euler.exe]
gcc -o euler.exe euler_number.c ../../../src/brz/* ../../../src/random-cross-platform/random_interface.c -I../../../include/ -lm

