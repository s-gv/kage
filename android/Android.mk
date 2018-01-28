LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE     := kage
LOCAL_C_INCLUDES += inc
LOCAL_SRC_FILES  := src/platform.c src/content.c src/game.c src/graphics.c src/audio.c src/al.c
LOCAL_CFLAGS     := -DANDROIDAPP -Wall -O2 -ftree-vectorize -std=gnu99 -ffast-math
LOCAL_LDFLAGS    := -lm -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)