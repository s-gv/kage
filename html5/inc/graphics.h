// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef KAGE_GRAPHICS_H
#define KAGE_GRAPHICS_H

#include <GLES2/gl2.h>

#include "stb_truetype.h"

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
    float aspect_ratio;

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
void GraphicsLoop(GraphicsState* graphics_state);

#endif