// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KAGE_GAME_H
#define KAGE_GAME_H

#include <GLES2/gl2.h>

#include "content.h"
#include "audio.h"

#define GAME_TICK_MS (1000.0f/60.0f)
#define MAX_ENTITY_PLANES 4
#define MAX_ENTITIES_PER_PLANE 512
#define MAX_Z_INDEXES 100

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
    Sprite *sprite;
    float x, y;
} Entity;

typedef struct {
    Entity entities[MAX_ENTITIES_PER_PLANE];
    int n_entities;
    int z_index;
    GLuint gl_vbo;
    GLuint gl_tex;
} EntityPlane;

typedef struct {
    GLuint gl_program;
    GLuint gl_pos_attrib;
    GLuint gl_tex_attrib;
    GLuint gl_mvp_uniform;
    GLuint gl_sampler_uniform;
} QuadShader;

typedef struct {
    float aspect_ratio;
    QuadShader quad_shader;

    int n_frames;

    EntityPlane planes[MAX_ENTITY_PLANES];
    int n_planes;

    float sprite_verts[3*2*MAX_ENTITIES_PER_PLANE*4];

    AudioState audio_state;
} GameState;

int GameInit(GameState* game_state);
void GameStateUpdate(GameState* game_state, GameInput game_input);
void GameRender(GameState* game_state);
void GameReset(GameState* game_state);

#endif