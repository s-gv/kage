#!/bin/bash

emcc -Wall -O2 -s USE_GLFW=3 -s TOTAL_MEMORY=536870912 --preload-file asset --js-library lib/libal.js -Iinc \
    src/platform.c src/game.c src/graphics.c src/audio.c src/content.c \
    -o bin/kage.html