#!/bin/bash

emcc -Wall -Wno-deprecated-declarations -O2 -s USE_GLFW=3 -s TOTAL_MEMORY=67108864 -Iinc \
    src/platform.c src/game.c \
    -o bin/kage.html