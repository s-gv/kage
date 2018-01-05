// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "game.h"
#include "platform.h"
#include "content.h"
#include "graphics.h"
#include "audio.h"

int GameInit(GameState* game_state)
{
    if(GraphicsInit(game_state) != 0) {
        LOGE("Error in graphics init.\n");
        return -1;
    }
    if(AudioInit(game_state) != 0) {
        LOGE("Audio init error.\n");
        return -1;
    }
    if(game_state->aspect_ratio == 0) {
        game_state->aspect_ratio = 16.0f/9.0f;
    }
    if(InitEntityPlane(&game_state->planes[0], "atlas.png") != 0) {
        LOGE("Entity plane init error\n");
        return -1;
    }
    game_state->n_planes = 1;
    LOGI("Game init done.\n");
    return 0;
}

void GameStateUpdate(GameState* game_state, GameInput game_input)
{
    EntityPlane *plane = &game_state->planes[0];

    float x = (game_state->n_frames % 50) / 50.0f, y = 0;
    Entity entity = {&g_sample_sprite, x, y};
    plane->entities[0] = entity;
    plane->n_entities = 1;

    game_state->n_frames++;
}

void GameRender(GameState* game_state)
{
    GraphicsLoop(game_state);
}

void GameReset(GameState* game_state)
{
    
}