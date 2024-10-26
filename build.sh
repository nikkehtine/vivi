#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra"
LIBS=$(pkg-config --libs raylib)

clang $CFLAGS -o vivi main.c $LIBS
