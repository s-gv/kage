#!/bin/bash

emcc -Wall -O2 -s USE_GLFW=3 -s TOTAL_MEMORY=67108864 --preload-file asset -Iinc \
    src/platform.c src/game.c src/graphics.c \
    -o bin/kage.html