// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "game.h"
#include "platform.h"
#include "content.h"
#include "graphics.h"
#include "audio.h"

int GameInit(GameState* game_state)
{
    memset(game_state, 0, sizeof(GameState));
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
    if(LoadTexture(&game_state->gl_target_tex, "target.png") != 0) {
        LOGE("Texture load error\n");
        return -1;
    }
    if(LoadTexture(&game_state->gl_kage_tex, "kage.png") != 0) {
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

int LoadTarget(int world_slice, Entity *entities, int n_entities)
{
    Entity es[3] = {
        (const Entity){&g_target_sprites[2*(rand() % N_ASSET_TARGETS)], world_slice*4000 - 1800, -800, ENTITY_TYPE_TARGET},
        (const Entity){&g_target_sprites[2*(rand() % N_ASSET_TARGETS)], world_slice*4000 - 200, -800, ENTITY_TYPE_TARGET},
        (const Entity){&g_target_sprites[2*(rand() % N_ASSET_TARGETS)], world_slice*4000 + 1800, -800, ENTITY_TYPE_TARGET}
    };
    for(int i = 0; i < 3; i++) {
        int res = AddEntity(es[i], entities, n_entities);
        if(res != 0) {
            return -1;
        }
    }
    return 0;
}

int LoadObstacle(int world_slice, Entity *entities, int n_entities)
{
    Entity es[1] = {
        (const Entity){&g_obstacle_sprites[0], world_slice*4000 - 1800, KAGE_UP_Y, ENTITY_TYPE_OBSTACLE}
    };
    /*
    if(world_slice % 3 == 1) {
        es[0].type = ENTITY_TYPE_OBSTACLE_MOVING;
    }*/
    for(int i = 0; i < 1; i++) {
        int res = AddEntity(es[i], entities, n_entities);
        if(res != 0) {
            return -1;
        }
    }
    return 0;
}

int LoadFood(int world_slice, Entity *entities, int n_entities)
{
    Entity es[3] = {
        (const Entity){&g_food_sprites[rand() % 4], world_slice*4000 - 1800, KAGE_DOWN_Y, ENTITY_TYPE_FOOD},
        (const Entity){&g_food_sprites[rand() % 4], world_slice*4000 - 200, KAGE_DOWN_Y, ENTITY_TYPE_FOOD_MOVING},
        (const Entity){&g_food_sprites[rand() % 4], world_slice*4000 + 1800, KAGE_NEUTRAL_Y, ENTITY_TYPE_FOOD}
    };
    for(int i = 0; i < 3; i++) {
        int res = AddEntity(es[i], entities, n_entities);
        if(res != 0) {
            return -1;
        }
    }
    return 0;
}

int LoadRoad(int world_slice, Entity *entities, int n_entities)
{
    Entity e = (const Entity){&g_roads[0], world_slice*4000, -900, ENTITY_TYPE_ROAD};
    return AddEntity(e, entities, n_entities);
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

void WriteInt(Entity *entities, int n_entities, int x, int y, int spacing, Sprite *num_sprites, int val)
{
    int i = 0;
    do {
        int v = (val % 10);
        val = val / 10;
        entities[i] = (const Entity){&num_sprites[v], x - spacing*i, y, ENTITY_TYPE_TEXT};
        i++;
        if(i >= n_entities) {
            break;
        }
    } while(val > 0);
}

int GetScore(GameState *game_state)
{
    return game_state->food_counter + 25*game_state->target_counter;
}

void GameStateUpdate(GameState* game_state, GameInput game_input)
{
    if(game_state->play_state == PLAY_STATE_START_SPLASH) {
        EntityPlane* splash_plane = &game_state->planes[0];
        splash_plane->gl_tex = game_state->gl_splash_tex;
        splash_plane->offset_x = 0;
        splash_plane->offset_y = 0;
        splash_plane->entities[0] = (const Entity){&g_start_splash_sprite, 0, 0, ENTITY_TYPE_SPLASH};

        game_state->n_planes = 1;

        if((game_input.event_type != GAME_INPUT_EVENT_NULL && game_input.event_type != GAME_INPUT_EVENT_PAUSE)
            || game_state->n_frames > 60) {
            game_state->play_state = PLAY_STATE_START_PLAY;
        }
    }
    else if(game_state->play_state == PLAY_STATE_START_PLAY) {
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
        farbg_plane->offset_x = 0;
        farbg_plane->offset_y = 0;
        ClearEntities(farbg_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadFarBg(0, farbg_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadFarBg(1, farbg_plane->entities, MAX_ENTITIES_PER_PLANE);

        EntityPlane* road_plane = &game_state->planes[1];
        road_plane->gl_tex = game_state->gl_kage_tex;
        road_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        road_plane->offset_x = 0;
        road_plane->offset_y = 0;
        ClearEntities(road_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadRoad(0, road_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadRoad(1, road_plane->entities, MAX_ENTITIES_PER_PLANE);

        EntityPlane* bg_plane = &game_state->planes[2];
        bg_plane->gl_tex = game_state->gl_bg_tex;
        bg_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        bg_plane->offset_x = 0;
        bg_plane->offset_y = 0;
        ClearEntities(bg_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadBg(0, bg_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadBg(1, bg_plane->entities, MAX_ENTITIES_PER_PLANE);

        EntityPlane* target_plane = &game_state->planes[3];
        target_plane->gl_tex = game_state->gl_target_tex;
        target_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        target_plane->offset_x = 0;
        target_plane->offset_y = 0;
        ClearEntities(target_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadTarget(0, target_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadTarget(1, target_plane->entities, MAX_ENTITIES_PER_PLANE);

        EntityPlane* player_plane = &game_state->planes[4];
        player_plane->gl_tex = game_state->gl_kage_tex;
        player_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        player_plane->offset_x = 0;
        player_plane->offset_y = 0;
        ClearEntities(player_plane->entities, MAX_ENTITIES_PER_PLANE);
        player_plane->entities[0] = (const Entity){&g_kage_sprites[0], KAGE_X, KAGE_NEUTRAL_Y, ENTITY_TYPE_PLAYER};

        EntityPlane* obstacle_plane = &game_state->planes[5];
        obstacle_plane->gl_tex = game_state->gl_bg_tex;
        obstacle_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        obstacle_plane->offset_x = 0;
        obstacle_plane->offset_y = 0;
        ClearEntities(obstacle_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadObstacle(0, obstacle_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadObstacle(1, obstacle_plane->entities, MAX_ENTITIES_PER_PLANE);

        EntityPlane* food_plane = &game_state->planes[6];
        food_plane->gl_tex = game_state->gl_bg_tex;
        food_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        food_plane->offset_x = 0;
        food_plane->offset_y = 0;
        ClearEntities(food_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadFood(0, food_plane->entities, MAX_ENTITIES_PER_PLANE);
        LoadFood(1, food_plane->entities, MAX_ENTITIES_PER_PLANE);

        EntityPlane* score_plane = &game_state->planes[7];
        score_plane->gl_tex = game_state->gl_kage_tex;
        score_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        score_plane->offset_x = 0;
        score_plane->offset_y = 0;
        ClearEntities(score_plane->entities, MAX_ENTITIES_PER_PLANE);

        EntityPlane* darken_plane = &game_state->planes[8];
        darken_plane->gl_tex = game_state->gl_kage_tex;
        darken_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        darken_plane->offset_x = 0;
        darken_plane->offset_y = 0;
        ClearEntities(darken_plane->entities, MAX_ENTITIES_PER_PLANE);

        EntityPlane* buttons_plane = &game_state->planes[9];
        buttons_plane->gl_tex = game_state->gl_kage_tex;
        buttons_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        buttons_plane->offset_x = 0;
        buttons_plane->offset_y = 0;
        ClearEntities(buttons_plane->entities, MAX_ENTITIES_PER_PLANE);

        game_state->food_counter = 0;
        game_state->target_counter = 0;

        game_state->n_planes = 10;
        game_state->n_frames = 0;

        game_state->play_state = PLAY_STATE_PLAYING;
    }
    else if(game_state->play_state == PLAY_STATE_PLAYING) {
        EntityPlane* farbg_plane = &game_state->planes[0];
        EntityPlane* road_plane = &game_state->planes[1];
        EntityPlane* bg_plane = &game_state->planes[2];
        EntityPlane* target_plane = &game_state->planes[3];
        EntityPlane* player_plane = &game_state->planes[4];
        EntityPlane* obstacle_plane = &game_state->planes[5];
        EntityPlane* food_plane = &game_state->planes[6];
        EntityPlane* score_plane = &game_state->planes[7];
        EntityPlane* darken_plane = &game_state->planes[8];
        EntityPlane* buttons_plane = &game_state->planes[9];

        if(((farbg_plane->offset_x+FARBG_SPEED) / WORLD_SLICE_WIDTH) > (farbg_plane->offset_x / WORLD_SLICE_WIDTH)) {
            ClearOldEntities(farbg_plane->entities, MAX_ENTITIES_PER_PLANE, farbg_plane->offset_x);
            int next_world_slice = ((farbg_plane->offset_x+FARBG_SPEED) / WORLD_SLICE_WIDTH) + 1;
            int res = LoadFarBg(next_world_slice, farbg_plane->entities, MAX_ENTITIES_PER_PLANE);
            if(res != 0) {
                LOGE("Out of space for entities\n");
            }
        }
        farbg_plane->offset_x += FARBG_SPEED;

        int speed = 0;
        if(game_state->n_frames < 2400) {
            speed = BG_SPEED0;
        }
        else if(game_state->n_frames < 9600) {
            speed = BG_SPEED1;
        }
        else {
            speed = BG_SPEED2;
        }
        if(((bg_plane->offset_x+speed) / WORLD_SLICE_WIDTH) > (bg_plane->offset_x / WORLD_SLICE_WIDTH)) {
            ClearOldEntities(road_plane->entities, MAX_ENTITIES_PER_PLANE, road_plane->offset_x);
            ClearOldEntities(bg_plane->entities, MAX_ENTITIES_PER_PLANE, bg_plane->offset_x);
            ClearOldEntities(target_plane->entities, MAX_ENTITIES_PER_PLANE, target_plane->offset_x);
            ClearOldEntities(obstacle_plane->entities, MAX_ENTITIES_PER_PLANE, obstacle_plane->offset_x);
            ClearOldEntities(food_plane->entities, MAX_ENTITIES_PER_PLANE, food_plane->offset_x);
            int next_world_slice = ((bg_plane->offset_x+speed) / WORLD_SLICE_WIDTH) + 1;
            int res1 = LoadBg(next_world_slice, bg_plane->entities, MAX_ENTITIES_PER_PLANE);
            int res2 = LoadRoad(next_world_slice, road_plane->entities, MAX_ENTITIES_PER_PLANE);
            int res3 = LoadTarget(next_world_slice, target_plane->entities, MAX_ENTITIES_PER_PLANE);
            int res4 = LoadObstacle(next_world_slice, obstacle_plane->entities, MAX_ENTITIES_PER_PLANE);
            int res5 = LoadFood(next_world_slice, food_plane->entities, MAX_ENTITIES_PER_PLANE);
            if(res1 != 0 || res2 != 0 || res3 != 0 || res4 != 0 || res5 != 0) {
                LOGE("Out of space for entities\n");
            }
        }
        road_plane->offset_x += speed;
        bg_plane->offset_x += speed;
        target_plane->offset_x += speed;
        obstacle_plane->offset_x += speed;
        food_plane->offset_x += speed;

        int score = GetScore(game_state);
        WriteInt(score_plane->entities, MAX_ENTITIES_PER_PLANE, 1575, 925, 60, &g_nums[0], score);
        darken_plane->entities[0] = (const Entity){NULL, 0, 0, ENTITY_TYPE_NULL};
        buttons_plane->entities[0] = (const Entity){&g_pause[0], 1725, 925, ENTITY_TYPE_BUTTON};
        
        if(game_state->kage_state == KAGE_MOVING_STRAIGHT) {
            if(game_input.event_type == GAME_INPUT_EVENT_SWIPE_UP) {
                game_state->kage_state = KAGE_MOVING_UP;
            }
            if(game_input.event_type == GAME_INPUT_EVENT_SWIPE_DOWN) {
                game_state->kage_state = KAGE_MOVING_DOWN;
            }
        }
        
        Entity* player_entity = &player_plane->entities[0];
        if(game_state->kage_state == KAGE_MOVING_UP && player_entity->y < KAGE_UP_Y) {
            player_entity->y += KAGE_SPEED_Y;
        }
        if(game_state->kage_state == KAGE_MOVING_DOWN && player_entity->y > KAGE_DOWN_Y) {
            player_entity->y -= KAGE_SPEED_Y;
        }
        if(player_entity->y == KAGE_NEUTRAL_Y || player_entity->y == KAGE_UP_Y || player_entity->y == KAGE_DOWN_Y) {
            game_state->kage_state = KAGE_MOVING_STRAIGHT;
        }

        player_entity->sprite = g_kage_anim.key_frames[game_state->player_kf_idx].sprite;
        game_state->player_kf_duration++;
        if(game_state->player_kf_duration >= g_kage_anim.key_frames[game_state->player_kf_idx].duration) {
            game_state->player_kf_idx++;
            if(game_state->player_kf_idx >= g_kage_anim.n_keyframes) {
                game_state->player_kf_idx = 0;
            }
            game_state->player_kf_duration = 0;
        }
        
        Entity* crap_entity = &player_plane->entities[1];
        if(game_state->crap_state == CRAP_NONE) {
            if(game_input.event_type == GAME_INPUT_EVENT_SWIPE_LEFT) {
                game_state->crap_state = CRAP_FALLING;
                alPlay(game_state->al_poop_buffer, AL_PLAY_ONCE);
                *crap_entity = (const Entity){&g_crap_sprites[rand() % 3], player_entity->x, player_entity->y, ENTITY_TYPE_CRAP};
            }
        }
        
        if(game_state->crap_state == CRAP_FALLING) {
            crap_entity->y -= CRAP_SPEED_Y;
            // Check if crap collided with targets
            for(int i = 0; i < MAX_ENTITIES_PER_PLANE; i++) {
                Entity* target = &target_plane->entities[i];
                if(target->type == ENTITY_TYPE_TARGET) {
                    int target_x = target->x - target_plane->offset_x;
                    int target_y = target->y - target_plane->offset_y;
                    if(abs(crap_entity->x - target_x) < 30 && abs(crap_entity->y - target_y) < 300) {
                        target->sprite++;
                        game_state->target_counter++;
                        game_state->crap_state = CRAP_NONE;
                        crap_entity->type = ENTITY_TYPE_NULL;
                    }
                }
            }
            if(crap_entity->y <= CRAP_MIN_Y) {
                game_state->crap_state = CRAP_FALLEN;
            }
        }

        if(game_state->crap_state == CRAP_FALLEN) {
            crap_entity->x -= speed;
            if(crap_entity->x < -2000) {
                game_state->crap_state = CRAP_NONE;
                crap_entity->type = ENTITY_TYPE_NULL;
            }
        }

        for(int i = 0; i < MAX_ENTITIES_PER_PLANE; i++) {
            Entity* food = &food_plane->entities[i];
            if(food->type == ENTITY_TYPE_FOOD || food->type == ENTITY_TYPE_FOOD_MOVING) {
                int food_x = food->x - food_plane->offset_x;
                int food_y = food->y - food_plane->offset_y;
                if(abs(player_entity->x - food_x) < 150 && abs(player_entity->y - food_y) < 20) {
                    game_state->food_counter++;
                    alPlay(game_state->al_crunch_buffer, AL_PLAY_ONCE);
                    food->type = ENTITY_TYPE_NULL;
                }
            }
            if(food->type == ENTITY_TYPE_FOOD_MOVING) {
                // Jumble up the phase and frequency to prevent synced movements of diffierent entities
                food->y = KAGE_NEUTRAL_Y + (KAGE_UP_Y - KAGE_NEUTRAL_Y) * sin(game_state->n_frames/(i % 4 + 25.0f) + 2*i);
            }
        }

        for(int i = 0; i < MAX_ENTITIES_PER_PLANE; i++) {
            Entity* obstacle = &obstacle_plane->entities[i];
            if(obstacle->type == ENTITY_TYPE_OBSTACLE || obstacle->type == ENTITY_TYPE_OBSTACLE_MOVING) {
                int obstacle_x = obstacle->x - obstacle_plane->offset_x;
                int obstacle_y = obstacle->y - obstacle_plane->offset_y;
                if(abs(player_entity->x - obstacle_x) < 350 && abs(player_entity->y - obstacle_y) < 20) {
                    game_state->play_state = PLAY_STATE_DYING;
                    game_state->player_kf_idx = 0;
                }
            }
            if(obstacle->type == ENTITY_TYPE_OBSTACLE_MOVING) {
                // Jumble up the phase and frequency to prevent synced movements of diffierent entities
                obstacle->y = KAGE_NEUTRAL_Y + (KAGE_UP_Y - KAGE_NEUTRAL_Y) * sin(game_state->n_frames/(i % 4 + 40.0f) + 4*i);
            }
        }

        if(rand() % 1000 == 0) {
            alPlay(game_state->al_crow_buffer, AL_PLAY_ONCE);
        }

        if(game_input.event_type == GAME_INPUT_EVENT_PAUSE) {
            game_state->play_state = PLAY_STATE_PAUSE;
            alSuspend();
        }
    }
    else if(game_state->play_state == PLAY_STATE_PAUSE) {
        EntityPlane* darken_plane = &game_state->planes[8];
        EntityPlane* buttons_plane = &game_state->planes[9];

        darken_plane->entities[0] = (const Entity){&g_darken[0], 0, 0, ENTITY_TYPE_SPLASH};
        buttons_plane->entities[0] = (const Entity){&g_play[0], 0, 0, ENTITY_TYPE_BUTTON};

        if(game_input.event_type != GAME_INPUT_EVENT_NULL && game_input.event_type != GAME_INPUT_EVENT_PAUSE) {
            game_state->play_state = PLAY_STATE_PLAYING;
            alResume();
        }
    }
    else if(game_state->play_state == PLAY_STATE_DYING) {
        EntityPlane* player_plane = &game_state->planes[4];
        Entity* player_entity = &player_plane->entities[0];

        player_entity->sprite = g_kage_dying_anim.key_frames[game_state->player_kf_idx].sprite;
        game_state->player_kf_duration++;
        if(game_state->player_kf_duration >= g_kage_dying_anim.key_frames[game_state->player_kf_idx].duration) {
            game_state->player_kf_idx++;
            game_state->player_kf_duration = 0;
            if(game_state->player_kf_idx >= g_kage_dying_anim.n_keyframes) {
                game_state->player_kf_idx = 0;
            }
        }
        player_entity->y -= 20;
        if(player_entity->y < -800) {
            game_state->play_state = PLAY_STATE_STOP_SPLASH;
        }
    }
    else if(game_state->play_state == PLAY_STATE_STOP_SPLASH) {
        EntityPlane* splash_plane = &game_state->planes[0];
        splash_plane->gl_tex = game_state->gl_splash_tex;
        splash_plane->offset_x = 0;
        splash_plane->offset_y = 0;
        splash_plane->entities[0] = (const Entity){&g_stop_splash_sprite, 0, 0, ENTITY_TYPE_SPLASH};

        EntityPlane* score_plane = &game_state->planes[1];
        score_plane->gl_tex = game_state->gl_kage_tex;
        score_plane->zoom = (1.0f/(WORLD_SLICE_WIDTH/4));
        score_plane->offset_x = 0;
        score_plane->offset_y = 0;
        ClearEntities(score_plane->entities, MAX_ENTITIES_PER_PLANE);

        int score = GetScore(game_state);
        int n_digits = 0;
        int tmp = score;
        do {
            tmp = tmp / 10;
            n_digits++;
        } while(tmp > 0);
        WriteInt(score_plane->entities, MAX_ENTITIES_PER_PLANE, 100*(n_digits - 1), 250, 120, &g_big_nums[0], score);

        game_state->n_planes = 2;

        if(game_input.event_type != GAME_INPUT_EVENT_NULL && game_input.event_type != GAME_INPUT_EVENT_PAUSE) {
            game_state->play_state = PLAY_STATE_START_PLAY;
        }
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
