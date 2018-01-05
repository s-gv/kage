// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KAGE_GRAPHICS_H
#define KAGE_GRAPHICS_H

#include "game.h"

int GraphicsInit(GameState* game_state);
int LoadTexture(GLuint *gl_tex, const char* file_name);
void GraphicsLoop(GameState* game_state);

#endif