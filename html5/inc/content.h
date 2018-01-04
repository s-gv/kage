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
    KeyFrame keyframes[MAX_KEYFRAMES];
    int n_keyframes;
} AnimSeq;

#endif