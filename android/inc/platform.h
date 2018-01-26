// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KAGE_PLATFORM_H
#define KAGE_PLATFORM_H

#include <stdio.h>
#include <android/log.h>

#define LOGI(M, ...)  __android_log_print(ANDROID_LOG_INFO, "NDK", "%s:%d. " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGD(M, ...)  __android_log_print(ANDROID_LOG_DEBUG, "NDK", "%s:%d. " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGE(M, ...)  __android_log_print(ANDROID_LOG_ERROR, "NDK", "%s:%d. " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

unsigned char* PlatformImgLoad(const char* fileName, int* width, int* height);
void PlatformImgFree(unsigned char* data);
FILE* platform_fopen(const char* fileName, const char* mode);
void platform_fclose(FILE* fp);

#endif