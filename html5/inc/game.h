// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KAGE_GAME_H
#define KAGE_GAME_H

#include <GLES2/gl2.h>

#include "content.h"

#define GAME_TICK_MS (1000.0f/60.0f)
#define MAX_ENTITY_PLANES 16
#define MAX_ENTITIES_PER_PLANE 16
#define WORLD_SLICE_WIDTH 4000

#define FARBG_SPEED 1
#define BG_SPEED 10

#define KAGE_X -1000
#define KAGE_NEUTRAL_Y 400
#define KAGE_UP_Y 700
#define KAGE_DOWN_Y 100
#define KAGE_SPEED_Y 30

#define CRAP_SPEED_Y 75
#define CRAP_MIN_Y -800

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

typedef enum {
    PLAY_STATE_START_SPLASH,
    PLAY_STATE_START_PLAY,
    PLAY_STATE_PAUSE,
    PLAY_STATE_PLAYING,
    PLAY_STATE_STOP_SPLASH,
    PLAY_STATE_DYING,
} PlayState;

typedef enum {
    ENTITY_TYPE_NULL,
    ENTITY_TYPE_SPLASH,
    ENTITY_TYPE_FARBG,
    ENTITY_TYPE_BG,
    ENTITY_TYPE_PLAYER,
    ENTITY_TYPE_CRAP,
    ENTITY_TYPE_TARGET,
    ENTITY_TYPE_FOOD,
    ENTITY_TYPE_OBSTACLE,
    ENTITY_TYPE_BUTTON,
    ENTITY_TYPE_TEXT,
} EntityType;

typedef enum {
    KAGE_MOVING_STRAIGHT,
    KAGE_MOVING_UP,
    KAGE_MOVING_DOWN
} KageState;

typedef enum {
    CRAP_NONE,
    CRAP_FALLING,
    CRAP_FALLEN
} CrapState;

typedef struct {
    Sprite *sprite;
    int x, y;
    EntityType type;
} Entity;

typedef struct {
    Entity entities[MAX_ENTITIES_PER_PLANE];
    GLuint gl_tex;
    int offset_x, offset_y;
    float zoom;
} EntityPlane;

typedef struct {
    GLuint gl_program;
    GLuint gl_pos_attrib;
    GLuint gl_tex_attrib;
    GLuint gl_mvp_uniform;
    GLuint gl_z_uniform;
    GLuint gl_sampler_uniform;
} QuadShader;

typedef struct {
    float aspect_ratio;
    QuadShader quad_shader;

    GLuint gl_splash_tex;
    GLuint gl_farbg_tex;
    GLuint gl_bg_tex;
    GLuint gl_kage_tex;
    GLuint gl_target_tex;

    EntityPlane planes[MAX_ENTITY_PLANES];
    GLuint gl_vbos[MAX_ENTITY_PLANES];
    int n_planes;

    int player_kf_idx;
    int player_kf_duration;

    float sprite_verts[3*2*MAX_ENTITIES_PER_PLANE*4];

    PlayState play_state;
    KageState kage_state;
    CrapState crap_state;

    int target_counter;
    int food_counter;

    int pos_x;

    int n_frames;

    int al_background_buffer;
    int al_background_source;
} GameState;

int GameInit(GameState* game_state);
void GameStateUpdate(GameState* game_state, GameInput game_input);
void GameRender(GameState* game_state);
void GameReset(GameState* game_state);

#endif