// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdlib.h>
#include <inttypes.h>

#include "audio.h"
#include "platform.h"

#define MAX_SAMPLES (1 << 23)

int wavBufferData(char* file_name) {
    int buffer_idx = 0;
    FILE* fp = platform_fopen(file_name, "rb");
    if (fp == NULL) {
        LOGE("Error opening audio file %s\n", file_name);
        return 0;
    }
    unsigned char* data = malloc(MAX_SAMPLES*4);
    float* samples = malloc(MAX_SAMPLES*sizeof(float));
    if (data == NULL || samples == NULL) {
        LOGE("Insufficient memory to load audio\n");
        fclose(fp);
        return 0;
    }
    fread(data, 1, 1 << 23, fp);
    int n_samples = *((uint32_t*)(&data[40])) / 2;
    n_samples = (n_samples < MAX_SAMPLES) ? n_samples : MAX_SAMPLES;
    int i;
    for(i = 0; i < n_samples; i++) {
        samples[i] = *((int16_t*)(&data[44+2*i])) / 32768.0f;
    }
    buffer_idx = alBufferData(1, 44100, samples, n_samples);
    fclose(fp);
    return buffer_idx;
}

int AudioInit(GameState* game_state)
{
    if(alInit() != 0) {
        LOGE("Audio Init failed\n");
        return 1;
    }
    game_state->al_background_buffer = wavBufferData("sky_high.wav");
    game_state->al_crow_buffer = wavBufferData("crow.wav");
    game_state->al_poop_buffer = wavBufferData("poop.wav");
    game_state->al_crunch_buffer = wavBufferData("crunch.wav");
    
    game_state->al_background_source = alPlay(game_state->al_background_buffer, AL_PLAY_INFINITE);

    LOGI("Audio init done.\n");
    return 0;
}