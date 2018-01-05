// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content.h"

Sprite g_sample_sprite = {
    (512.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
    (639.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
    1.0f, 1.0f,
};

Sprite g_start_splash_sprite = {
    (0000.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
    (1023.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
    4.0f, 2.0f,
};

Sprite g_bg_sprite = {
    (0000.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
    (1023.0f + 0.5f)/1024.0f, (512.0f + 0.5f)/1024.0f,
    4.0f, 2.0f,
};