// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef KAGE_GRAPHICS_H
#define KAGE_GRAPHICS_H

#include <GLES2/gl2.h>

#include "stb_truetype.h"

#define MAX_ENTITIES_PER_PLANE 512
#define MAX_Z_INDEXES 100

typedef struct {
    GLuint gl_tex;
    stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
} FontFace;

typedef struct {
    GLuint gl_program;
    GLuint gl_pos_attrib;
    GLuint gl_tex_attrib;
    GLuint gl_mvp_uniform;
    GLuint gl_color_uniform;
    GLuint gl_sampler_uniform;
    GLuint gl_vbo;
} FontShader;

typedef struct {
    float x0, y0, s0, t0; // left-top
    float x1, y1, s1, t1; // right-bottom
} Entity;

typedef struct {
    Entity entities[MAX_ENTITIES_PER_PLANE];
    int n_entities;
    int z_index;
    int gl_vbo;
    int gl_tex;
} EntityPlane;

typedef struct {
    float aspect_ratio;
    EntityPlane planes[4];

    GLuint gl_simple_shader;
    GLuint gl_pos_attrib;
    GLuint gl_tex_attrib;
    GLuint gl_mvp_uniform;
    GLuint gl_sampler_uniform;
    GLuint gl_vbo;
    GLuint gl_tex;

    FontFace font;
    FontShader font_shader;
} GraphicsState;

int GraphicsInit(GraphicsState* graphics_state);
int InitEntityPlane(EntityPlane* plane, const char* atlas_file_name);
void GraphicsLoop(GraphicsState* graphics_state);

#endif