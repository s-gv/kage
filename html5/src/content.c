// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content.h"

Sprite g_kage0_sprite = {
    (640.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
    (767.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
    0.5f, 0.5f,
};

Sprite g_kage1_sprite = {
    (768.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
    (895.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
    0.5f, 0.5f,
};

Sprite g_kage2_sprite = {
    (896.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
    (1023.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
    0.5f, 0.5f,
};

Sprite g_start_splash_sprite = {
    (0000.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
    (1023.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
    4.0f, 2.0f,
};

Sprite g_bg_sun_sprite = {
    (000.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
    (127.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
    0.5f, 0.5f,
};

AnimSeq g_kage_anim = {
    {
        {&g_kage0_sprite, 5},
        {&g_kage1_sprite, 5},
        {&g_kage2_sprite, 5},
        {&g_kage2_sprite, 5},
        {&g_kage1_sprite, 5},
        {&g_kage0_sprite, 5},
    },
    6
};