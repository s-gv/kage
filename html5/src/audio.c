// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdlib.h>
#include <inttypes.h>

#include "audio.h"
#include "platform.h"

int wavBufferData(char* file_name) {
    int buffer_idx = 0;
    FILE* fp = platform_fopen(file_name, "rb");
    if (fp == NULL) {
        LOGE("Error opening audio file %s\n", file_name);
        return 0;
    }
    unsigned char* data = malloc(1 << 23);
    float* samples = malloc((1 << 21)*sizeof(float));
    if (data == NULL || samples == NULL) {
        LOGE("Insufficient memory to load audio\n");
        fclose(fp);
        return 0;
    }
    fread(data, 1, 1 << 23, fp);
    int n_samples = *((uint32_t*)(&data[40])) / 2;
    int i;
    for(i = 0; i < n_samples; i++) {
        samples[i] = *((int16_t*)(&data[44+2*i])) / 32768.0f;
    }
    // buffer_idx = alBufferData(1, 44100, samples, n_samples);
    fclose(fp);
    return buffer_idx;
}

int AudioInit(GameState* game_state)
{
    /*
    if(alInit() != 0) {
        LOGE("Audio Init failed\n");
        return 1;
    }
    */
    game_state->al_background_buffer = wavBufferData("sky_high.wav");
    //game_state->al_background_source = alPlay(game_state->al_background_buffer, AL_PLAY_INFINITE);
    LOGI("Audio init done.\n");
    return 0;
}