// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KAGE_AUDIO_H
#define KAGE_AUDIO_H

typedef struct {
    int al_background_buffer;
    int al_background_source;
} AudioState;

typedef enum {
    AL_PLAY_ONCE,
    AL_PLAY_INFINITE,
} LIB_AUDIO_MODE;

// Public init
int AudioInit(AudioState* audio_state);

// Private init. returns 0 on success
int alInit();

// returns an integer that represents the buffer.
// If stereo buffer, data is (left0, right0, left1, right1) and data_count = 4
int alBufferData(int n_channels, int sample_rate, float* data, int data_count);

// Destroy buffer from memory
void alDestroyBuffer(int buffer);

// returns an integer representing the playing sound.
int alPlay(int buffer, int mode);

// stop playing sound
void alStop(int source);

// Pause all playing sounds
void alSuspend();

// Resume any sounds that were playing when suspended
void alResume();

#endif