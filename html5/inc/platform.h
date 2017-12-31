// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef KAGE_PLATFORM_H
#define KAGE_PLATFORM_H

#include <stdio.h>

#define LOGI(M, ...)  printf("[INFO] %s:%d - " M "", __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGD(M, ...)  printf("[DEBUG] %s:%d - " M "", __FILE__, __LINE__, ##__VA_ARGS__)
#define LOGE(M, ...)  printf("[ERROR] %s:%d - " M "", __FILE__, __LINE__, ##__VA_ARGS__)

unsigned char* PlatformImgLoad(char* fileName, int* width, int* height);
void PlatformImgFree(unsigned char* data);
FILE* platform_fopen(const char* fileName, const char* mode);
void platform_fclose(FILE* fp);

#endif