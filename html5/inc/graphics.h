// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#ifndef KAGE_GRAPHICS_H
#define KAGE_GRAPHICS_H

#include <GLES2/gl2.h>

typedef struct {
    GLuint gl_simple_shader;
    GLuint gl_pos_attrib;
    GLuint gl_tex_attrib;
    GLuint gl_sampler_uniform;
    GLuint gl_vbo;
    GLuint gl_tex;
} GraphicsState;

int GraphicsInit(GraphicsState* graphics_state);
void GraphicsLoop(GraphicsState* graphics_state);

#endif