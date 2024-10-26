#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra"
LIBS="$(pkg-config --libs --cflags raylib) -lglfw -lm -ldl -lpthread"

clang $CFLAGS -o vivi main.c $LIBS
