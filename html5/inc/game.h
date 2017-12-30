// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef KAGE_GAME_H
#define KAGE_GAME_H

#include "graphics.h"

#define GAME_TICK_MS (1000.0f/30.0f)

typedef enum {
    GAME_INPUT_EVENT_NULL,
    GAME_INPUT_EVENT_SWIPE_UP,
    GAME_INPUT_EVENT_SWIPE_DOWN,
    GAME_INPUT_EVENT_SWIPE_LEFT,
    GAME_INPUT_EVENT_SWIPE_RIGHT,
    GAME_INPUT_EVENT_PAUSE,
    GAME_INPUT_EVENT_PRESS,
} GameInputEventType;

typedef struct {
    GameInputEventType event_type;
    float x; // (0,0) is left-top and (1,1) is right-bottom
    float y;
} GameInput;

typedef struct {
    GraphicsState graphics_state;
} GameState;

int GameInit(GameState* game_state);
void GameStateUpdate(GameState* game_state, GameInput game_input);
void GameRender(GameState* game_state);
void GameReset(GameState* game_state);

#endif