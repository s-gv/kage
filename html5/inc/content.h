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
extern Sprite g_kage_sprites[8];
extern Sprite g_crap_sprites[3];
extern Sprite g_target_sprites[8];
extern Sprite g_food_sprites[4];
extern Sprite g_obstacle_sprites[1];
extern Sprite g_stop_splash_sprite;
extern Sprite g_kage_dying_sprites[8];
extern Sprite g_darken[1];
extern Sprite g_play[1];
extern Sprite g_pause[1];

extern AnimSeq g_kage_anim;
extern AnimSeq g_kage_dying_anim;

#endif