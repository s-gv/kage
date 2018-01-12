// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KAGE_CONTENT_H
#define KAGE_CONTENT_H

#define MAX_KEYFRAMES 64

typedef struct {
    float s0, t0; // left-top
    float s1, t1; // right-bottom
    float w, h;
} Sprite;

typedef struct {
    Sprite *sprite;
    int duration; // in multiples of 33.33ms
} KeyFrame;

typedef struct {
    KeyFrame key_frames[MAX_KEYFRAMES];
    int n_keyframes;
} AnimSeq;

extern Sprite g_start_splash_sprite;
extern Sprite g_farbg_sprites[2];
extern Sprite g_cloud_sprites[4];
extern Sprite g_bush_sprites[4];
extern Sprite g_building_sprites[8];

extern AnimSeq g_kage_anim;

#endif