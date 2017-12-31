// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "game.h"
#include "platform.h"

int GameInit(GameState* game_state)
{
    if(GraphicsInit(&game_state->graphics_state) != 0) {
        LOGE("Error in graphics init.\n");
        return -1;
    }
    game_state->graphics_state.aspect_ratio = 16.0f/9.0f;
    LOGI("Game init done.\n");
    return 0;
}

void GameStateUpdate(GameState* game_state, GameInput game_input)
{

}

void GameRender(GameState* game_state)
{
    GraphicsLoop(&game_state->graphics_state);
}

void GameReset(GameState* game_state)
{
    
}