// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdlib.h>

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

int AddEntity(Entity entity, Entity *entities, int n_entities)
{
    for(int i = 0; i < n_entities; i++) {
        Entity *e = &entities[i];
        if(e->type == ENTITY_TYPE_NULL) {
            *e = entity;
            return 0;
        }
    }
    return -1;
}

int LoadFarBg(int world_slice, Entity *entities, int n_entities)
{
    Entity e = (const Entity){&g_farbg_sprites[world_slice % 2], world_slice*4000, 0, ENTITY_TYPE_FARBG};
    return AddEntity(e, entities, n_entities);
}
int LoadBg(int world_slice, Entity *entities, int n_entities)
{
    Entity es[3] = {
        (const Entity){&g_cloud_sprites[rand() % 4], world_slice*4000, 600, ENTITY_TYPE_BG},
        (const Entity){&g_bush_sprites[rand() % 4], world_slice*4000 -1000, -400, ENTITY_TYPE_BG},
        (const Entity){&g_building_sprites[rand() % 8], world_slice*4000 + 1000, -400, ENTITY_TYPE_BG}
    };
    for(int i = 0; i < 3; i++) {
        int res = AddEntity(es[i], entities, n_entities);
        if(res != 0) {
            return -1;
        }
    }
    return 0;
}

void ClearEntities(Entity *entities, int n_entities)
{
    for(int i = 0; i < n_entities; i++) {
        entities[i].type = ENTITY_TYPE_NULL;
    }
}
void ClearOldEntities(Entity *entities, int n_entities, int world_x)
{
    for(int i = 0; i < n_entities; i++) {
        Entity *entity = &entities[i];
        if((entity->x - world_x) < -WORLD_SLICE_WIDTH) {
            entity->type = ENTITY_TYPE_NULL;
        }
    }
}

void GameStateUpdate(GameState* game_state, GameInput game_input)
{
    if(game_state->play_state == PLAY_STATE_START_SPLASH) {
        EntityPlane* splash_plane = &game_state->planes[0];
        splash_plane->gl_tex = game_state->gl_splash_tex;
        splash_plane->entities[0] = (const Entity){&g_start_splash_sprite, 0, 0, ENTITY_TYPE_SPLASH};

        game_state->n_planes = 1;

        if(game_input.event_type != GAME_INPUT_EVENT_NULL || game_state->n_frames > 60) {
            game_state->play_state = PLAY_STATE_START_PLAY;
        }
    }
    if(game_state->play_state == PLAY_STATE_START_PLAY) {
        // Horizontally scrolling world looks like this:
        //
        //            Slice 0          Slice 1          Slice 2
        //      |                |                |                |
        //      |                |                |                |
        //      |        *       |        *       |        *       |
        //      |                |                |                |
        //      |                |                |                |
        // x: -2000      0      2000     4000    6000     8000    10000
        // ymin: -1000; ymax: +1000

        EntityPlane* farbg_plane = &game_state->planes[0];
        farbg_plane->gl_tex = game_state->gl_farbg_tex;
        farbg_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        ClearEntities(farbg_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadFarBg(0, farbg_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadFarBg(1, farbg_plane->entities, MAX_ENTITIES_PER_PLANE);

        EntityPlane* bg_plane = &game_state->planes[1];
        bg_plane->gl_tex = game_state->gl_bg_tex;
        bg_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        ClearEntities(bg_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadBg(0, bg_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadBg(1, bg_plane->entities, MAX_ENTITIES_PER_PLANE);

        EntityPlane* player_plane = &game_state->planes[2];
        player_plane->gl_tex = game_state->gl_bg_tex;
        player_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        ClearEntities(player_plane->entities, MAX_ENTITIES_PER_PLANE);
        player_plane->entities[0] = (const Entity){&g_kage_sprites[0], -1000, 250, ENTITY_TYPE_PLAYER};

        game_state->n_planes = 3;

        game_state->play_state = PLAY_STATE_PLAYING;
    }
    if(game_state->play_state == PLAY_STATE_PLAYING) {
        EntityPlane* farbg_plane = &game_state->planes[0];
        EntityPlane* bg_plane = &game_state->planes[1];
        EntityPlane* player_plane = &game_state->planes[2];

        if(((farbg_plane->offset_x+FARBG_SPEED) / WORLD_SLICE_WIDTH) > (farbg_plane->offset_x / WORLD_SLICE_WIDTH)) {
            ClearOldEntities(farbg_plane->entities, MAX_ENTITIES_PER_PLANE, farbg_plane->offset_x);
            int next_world_slice = ((farbg_plane->offset_x+FARBG_SPEED) / WORLD_SLICE_WIDTH) + 1;
            int res = LoadFarBg(next_world_slice, farbg_plane->entities, MAX_ENTITIES_PER_PLANE);
            if(res != 0) {
                LOGE("Out of space for entities\n");
            }
        }
        farbg_plane->offset_x += FARBG_SPEED;

        if(((bg_plane->offset_x+BG_SPEED) / WORLD_SLICE_WIDTH) > (bg_plane->offset_x / WORLD_SLICE_WIDTH)) {
            ClearOldEntities(bg_plane->entities, MAX_ENTITIES_PER_PLANE, bg_plane->offset_x);
            int next_world_slice = ((bg_plane->offset_x+BG_SPEED) / WORLD_SLICE_WIDTH) + 1;
            int res = LoadBg(next_world_slice, bg_plane->entities, MAX_ENTITIES_PER_PLANE);
            if(res != 0) {
                LOGE("Out of space for entities\n");
            }
        }
        bg_plane->offset_x += BG_SPEED;

        player_plane->entities[0].sprite = g_kage_anim.key_frames[game_state->player_kf_idx].sprite;
        game_state->player_kf_duration++;
        if(game_state->player_kf_duration >= g_kage_anim.key_frames[game_state->player_kf_idx].duration) {
            game_state->player_kf_idx++;
            if(game_state->player_kf_idx >= g_kage_anim.n_keyframes) {
                game_state->player_kf_idx = 0;
            }
            game_state->player_kf_duration = 0;
        }

        game_state->n_planes = 3;
        

        /*
        EntityPlane* bg_plane = &game_state->planes[1];
        bg_plane->gl_tex = game_state->gl_bg_tex;

        // Move all objects to the left (or equivalently, the camera to the right)
        game_state->pos_x += 0.005;
        float farbg_speed = 0.005;
        farbg_plane->entities[0].x -= farbg_speed;
        farbg_plane->entities[1].x -= farbg_speed;
        

        if(game_state->pos_x > 4.0f) {
            

            // Load new entities for the next slice
            float offset_x = 4.0f;
            float offset_y = 0;
            
            //
        }
        double farbg_pos_x = game_state->pos_x / 4;
        double farbg_cam_pos_x = farbg_pos_x - (((int)(farbg_pos_x))/4)*4;
        int farbg_cur_idx = 0;
        int farbg_next_idx = 1;
        if(((int)(farbg_pos_x))/4 % 2 == 1) {
            farbg_cur_idx = 1;
            farbg_next_idx = 0;
        }
        
        farbg_plane->entities[0] = (const Entity){&g_farbg_sprites[farbg_cur_idx], 0.0f - farbg_cam_pos_x, 0.0f};
        farbg_plane->entities[1] = (const Entity){&g_farbg_sprites[farbg_next_idx], 4.0f - farbg_cam_pos_x, 0.0f};
        farbg_plane->n_entities = 2;

        
        
        
        bg_plane->n_entities = 3;
        
        
        

        player_plane->n_entities = 1;
        */
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