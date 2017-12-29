// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include <GLES2/gl2.h>

#include "game.h"

void GameInit(GameState* game_state)
{
    
}

void GameStateUpdate(GameState* game_state, GameInput game_input)
{

}

void GameRender(GameState* game_state)
{
    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GameReset(GameState* game_state)
{
    
}