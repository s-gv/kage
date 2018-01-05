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
    if(LoadTexture(&game_state->gl_sample_tex, "atlas.png") != 0) {
        LOGE("Texture load error\n");
        return -1;
    }
    if(LoadTexture(&game_state->gl_splash_tex, "splash.png") != 0) {
        LOGE("Texture load error\n");
        return -1;
    }
    if(LoadTexture(&game_state->gl_bg_tex, "bg.png") != 0) {
        LOGE("Texture load error\n");
        return -1;
    }
    LOGI("Game init done.\n");
    return 0;
}

void GameStateUpdate(GameState* game_state, GameInput game_input)
{
    if(game_state->play_state == PLAY_STATE_START_SPLASH) {
        EntityPlane* splash_plane = &game_state->planes[0];
        splash_plane->gl_tex = game_state->gl_splash_tex;
        splash_plane->entities[0] = (const Entity){&g_start_splash_sprite, 0, 0};
        splash_plane->n_entities = 1;

        game_state->n_planes = 1;

        if(game_input.event_type != GAME_INPUT_EVENT_NULL) {
            game_state->play_state = PLAY_STATE_PLAYING;
        }
    }
    if(game_state->play_state == PLAY_STATE_PLAYING) {
        EntityPlane* bg_plane = &game_state->planes[0];
        bg_plane->gl_tex = game_state->gl_bg_tex;
        bg_plane->entities[0] = (const Entity){&g_start_splash_sprite, 0, 0};
        bg_plane->n_entities = 1;
        
        EntityPlane* sample_plane = &game_state->planes[1];
        sample_plane->gl_tex = game_state->gl_sample_tex;
        sample_plane->entities[0] = (const Entity){&g_sample_sprite, 0, 0};
        sample_plane->n_entities = 1;
        
        game_state->n_planes = 2;
    }
    game_state->n_frames++;
}

void GameRender(GameState* game_state)
{
    GraphicsLoop(game_state);
}

void GameReset(GameState* game_state)
{
    
}