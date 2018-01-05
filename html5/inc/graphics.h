// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KAGE_GRAPHICS_H
#define KAGE_GRAPHICS_H

#include <GLES2/gl2.h>

#include "content.h"

#define MAX_ENTITY_PLANES 4
#define MAX_ENTITIES_PER_PLANE 512
#define MAX_Z_INDEXES 100

typedef struct {
    GLuint gl_program;
    GLuint gl_pos_attrib;
    GLuint gl_tex_attrib;
    GLuint gl_mvp_uniform;
    GLuint gl_sampler_uniform;
} QuadShader;

typedef struct {
    Sprite *sprite;
    int x, y;
} Entity;

typedef struct {
    Entity entities[MAX_ENTITIES_PER_PLANE];
    int n_entities;
    int z_index;
    GLuint gl_vbo;
    GLuint gl_tex;
} EntityPlane;

typedef struct {
    float aspect_ratio;
    QuadShader quad_shader;

    EntityPlane planes[MAX_ENTITY_PLANES];
    int n_planes;

    float sprite_verts[3*2*MAX_ENTITIES_PER_PLANE*4];
} GraphicsState;

int GraphicsInit(GraphicsState* graphics_state);
int InitEntityPlane(EntityPlane* plane, const char* atlas_file_name);
void GraphicsLoop(GraphicsState* graphics_state);

#endif