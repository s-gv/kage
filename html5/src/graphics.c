// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "graphics.h"
#include "game.h"
#include "platform.h"

#define glChk() gl_check_for_errors(__FILE__, __LINE__);

static void gl_check_for_errors(char* fileName, int lineNum)
{
    GLint error;
    char errorString[1000];
    for (error = glGetError(); error; error = glGetError())
    {
        switch(error)
        {
            case GL_INVALID_ENUM: sprintf(errorString, "GL_INVALID_ENUM"); break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: sprintf(errorString, "GL_INVALID_FRAMEBUFFER_OPERATION"); break;
            case GL_INVALID_VALUE: sprintf(errorString, "GL_INVALID_VALUE"); break;
            case GL_INVALID_OPERATION: sprintf(errorString, "GL_INVALID_OPERATION"); break;
            case GL_OUT_OF_MEMORY: sprintf(errorString, "GL_OUT_OF_MEMORY"); break;
            default: sprintf(errorString, "Unknown GL error"); break;
        }
        LOGE("OpenGL error in file %s in line %d. Error code: %d. Error desc: %s\n", fileName, lineNum, error, errorString);
    }
}

static GLuint compileShader(GLenum shader_type, const GLchar* shader_source)
{
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        LOGE("Shader compile error: %s.\nShader source: %s\n", buffer, shader_source);
    }
    return shader;
}

static GLuint linkShader(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    GLint linkStatus = GL_FALSE;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE)
    {
        char buffer[512];
        glGetShaderInfoLog(shaderProgram, 512, NULL, buffer);
        LOGE("Shader link error: %s\n", buffer);
    }
    return shaderProgram;
}

static GLuint makeShaderProgram(const GLchar* vertex_src, const GLchar* fragment_src)
{
    GLuint gl_vert_shader = compileShader(GL_VERTEX_SHADER, vertex_src);
    GLuint gl_frag_shader = compileShader(GL_FRAGMENT_SHADER, fragment_src);
    return linkShader(gl_vert_shader, gl_frag_shader);
}

int GraphicsInit(GameState* game_state)
{
    // Quad shader
    const GLchar* vertex_src =
        "precision highp float;\n"
        "attribute vec2 a_pos;\n"
        "attribute vec2 a_tex;\n"
        "uniform mat4 u_mvp;\n"
        "uniform float u_z;"
        "varying vec2 v_tex;\n"
        "void main() {\n"
        "    gl_Position = u_mvp * vec4(a_pos.xy, u_z, 1.0);\n"
        "    v_tex = a_tex;\n"
        "}\n";
    const GLchar* fragment_src =
        "precision highp float;\n"
        "uniform sampler2D u_sampler;\n"
        "varying vec2 v_tex;\n"
        "void main() {\n"
        "    gl_FragColor = texture2D(u_sampler, v_tex);\n"
        "}\n";
    game_state->quad_shader.gl_program = makeShaderProgram(vertex_src, fragment_src);
    game_state->quad_shader.gl_pos_attrib = glGetAttribLocation(game_state->quad_shader.gl_program, "a_pos");
    game_state->quad_shader.gl_tex_attrib = glGetAttribLocation(game_state->quad_shader.gl_program, "a_tex");
    game_state->quad_shader.gl_sampler_uniform = glGetUniformLocation(game_state->quad_shader.gl_program, "u_sampler");
    game_state->quad_shader.gl_mvp_uniform = glGetUniformLocation(game_state->quad_shader.gl_program, "u_mvp");
    game_state->quad_shader.gl_z_uniform = glGetUniformLocation(game_state->quad_shader.gl_program, "u_z");

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for(int i = 0; i < MAX_ENTITY_PLANES; i++) {
        glGenBuffers(1, &game_state->gl_vbos[i]);
        glBindBuffer(GL_ARRAY_BUFFER, game_state->gl_vbos[i]);
        glBufferData(GL_ARRAY_BUFFER, 3*2*MAX_ENTITIES_PER_PLANE*4*sizeof(float), NULL, GL_STREAM_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glChk();

    LOGI("Graphics init done.\n");
    return 0;
}

int LoadTexture(GLuint *gl_tex, const char* file_name)
{
    int img_w, img_h;
    unsigned char* pixel_data = PlatformImgLoad(file_name, &img_w, &img_h);
    if (pixel_data == NULL) {
        LOGE("Failed to load texture image: %s\n", file_name);
        return 1;
    }

    glGenTextures(1, gl_tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *gl_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_w, img_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data);

    PlatformImgFree(pixel_data);

    return 0;
}

void GraphicsLoop(GameState* game_state)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float mvp_matrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    mvp_matrix[0] = 1.0f / game_state->aspect_ratio;

    for(int i = 0; i < game_state->n_planes; i++) {
        EntityPlane *plane = &game_state->planes[i];
        int offset_x = plane->offset_x;
        int offset_y = plane->offset_y;
        float zoom = plane->zoom;

        for(int j = 0; j < MAX_ENTITIES_PER_PLANE; j++) {
            Entity *entity = &plane->entities[j];
            Sprite *sprite = entity->sprite;

            float s0 = sprite->s0; float t0 = sprite->t0;
            float s1 = sprite->s1; float t1 = sprite->t1;
            float x0 = (entity->x-offset_x)*zoom - sprite->w/2; float y0 = (entity->y-offset_y)*zoom + sprite->h/2;
            float x1 = (entity->x-offset_x)*zoom + sprite->w/2; float y1 = (entity->y-offset_y)*zoom - sprite->h/2;

            if(entity->type == ENTITY_TYPE_NULL) {
                x0 = -10.0f; x1 = -10.0f; y0 = -10.0f; y1 = -10.0f;
            }

            float *qverts = &game_state->sprite_verts[24*j];

            // Triangle 0 of the quad
            qverts[0] = x0; qverts[1] = y0; qverts[2] = s0; qverts[3] = t0;
            qverts[4] = x1; qverts[5] = y1; qverts[6] = s1; qverts[7] = t1;
            qverts[8] = x0; qverts[9] = y1; qverts[10] = s0; qverts[11] = t1;

            // Triangle 1 of the quad
            qverts[12] = x0; qverts[13] = y0; qverts[14] = s0; qverts[15] = t0;
            qverts[16] = x1; qverts[17] = y0; qverts[18] = s1; qverts[19] = t0;
            qverts[20] = x1; qverts[21] = y1; qverts[22] = s1; qverts[23] = t1;
        }

        glUseProgram(game_state->quad_shader.gl_program); // Render quads

        glBindBuffer(GL_ARRAY_BUFFER, game_state->gl_vbos[i]);
        glBufferData(GL_ARRAY_BUFFER, 3*2*MAX_ENTITIES_PER_PLANE*4*sizeof(float), NULL, GL_STREAM_DRAW);
        glBufferData(GL_ARRAY_BUFFER, 3*2*MAX_ENTITIES_PER_PLANE*4*sizeof(float), game_state->sprite_verts, GL_STREAM_DRAW);

        glVertexAttribPointer(game_state->quad_shader.gl_pos_attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
        glEnableVertexAttribArray(game_state->quad_shader.gl_pos_attrib);
        glVertexAttribPointer(game_state->quad_shader.gl_tex_attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
        glEnableVertexAttribArray(game_state->quad_shader.gl_tex_attrib);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, plane->gl_tex);
        glUniform1i(game_state->quad_shader.gl_sampler_uniform, 0);

        glUniform1f(game_state->quad_shader.gl_z_uniform, (i*-1.0f)/MAX_ENTITY_PLANES);

        glUniformMatrix4fv(game_state->quad_shader.gl_mvp_uniform, 1, GL_FALSE, mvp_matrix);

        glDrawArrays(GL_TRIANGLES, 0, 6 * MAX_ENTITIES_PER_PLANE);
    }
    
    //glChk();
}