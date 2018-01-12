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
    if(LoadTexture(&game_state->gl_farbg_tex, "farbg.png") != 0) {
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

        if(game_input.event_type != GAME_INPUT_EVENT_NULL || game_state->n_frames > 60) {
            game_state->play_state = PLAY_STATE_PLAYING;
        }
    }
    if(game_state->play_state == PLAY_STATE_PLAYING) {
        EntityPlane* farbg_plane = &game_state->planes[0];
        farbg_plane->gl_tex = game_state->gl_farbg_tex;
        farbg_plane->entities[0] = (const Entity){&g_farbg_sprites[0], 0.0f, 0.0f};
        farbg_plane->n_entities = 1;

        EntityPlane* bg_plane = &game_state->planes[1];
        bg_plane->gl_tex = game_state->gl_bg_tex;
        bg_plane->entities[0] = (const Entity){&g_cloud_sprites[0], 0.0f, 0.6f};
        bg_plane->entities[1] = (const Entity){&g_bush_sprites[0], -1.0f, -0.4f};
        bg_plane->entities[2] = (const Entity){&g_building_sprites[0], 1.0f, -0.4f};
        bg_plane->n_entities = 3;
        
        EntityPlane* player_plane = &game_state->planes[2];
        player_plane->gl_tex = game_state->gl_bg_tex;
        player_plane->entities[0] = (const Entity){NULL, -1.0f, 0.25f};
        player_plane->entities[0].sprite = g_kage_anim.key_frames[game_state->player_kf_idx].sprite;
        game_state->player_kf_duration++;
        if(game_state->player_kf_duration >= g_kage_anim.key_frames[game_state->player_kf_idx].duration) {
            game_state->player_kf_idx++;
            if(game_state->player_kf_idx >= g_kage_anim.n_keyframes) {
                game_state->player_kf_idx = 0;
            }
            game_state->player_kf_duration = 0;
        }

        player_plane->n_entities = 1;
        
        game_state->n_planes = 3;
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