// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include "graphics.h"
#include "platform.h"

#define glChk() gl_check_for_errors(__FILE__, __LINE__);

void gl_check_for_errors(char* fileName, int lineNum)
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

GLuint compileShader(GLenum shader_type, const GLchar* shader_source)
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

GLuint linkShader(GLuint vertexShader, GLuint fragmentShader)
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

GLuint makeShaderProgram(const GLchar* vertex_src, const GLchar* fragment_src)
{
    GLuint gl_vert_shader = compileShader(GL_VERTEX_SHADER, vertex_src);
    GLuint gl_frag_shader = compileShader(GL_FRAGMENT_SHADER, fragment_src);
    return linkShader(gl_vert_shader, gl_frag_shader);
}

float sample_verts[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.0f,  0.5f,
};

int GraphicsInit(GraphicsState* graphics_state)
{
    const GLchar* vertex_src =
        "precision highp float;\n"
        "attribute vec2 a_pos;\n"
        "void main() {\n"
        "    gl_Position = vec4(a_pos.x, a_pos.y, 0.0, 1.0);\n"
        "}\n";
    const GLchar* fragment_src =
        "precision highp float;\n"
        "void main() {\n"
        "    gl_FragColor =  vec4(0.5, 0.0, 0.0, 1.0);\n"
        "}\n";
    graphics_state->gl_simple_shader = makeShaderProgram(vertex_src, fragment_src);
    graphics_state->gl_pos_attrib = glGetAttribLocation(graphics_state->gl_simple_shader, "a_pos");

    glGenBuffers(1, &graphics_state->gl_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, graphics_state->gl_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sample_verts), sample_verts, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glChk();

    LOGI("Graphics init done.\n");
    return 0;
}

void GraphicsLoop(GraphicsState* graphics_state)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(graphics_state->gl_simple_shader);
    glBindBuffer(GL_ARRAY_BUFFER, graphics_state->gl_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sample_verts), NULL, GL_STREAM_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sample_verts), sample_verts, GL_STREAM_DRAW);
    glEnableVertexAttribArray(graphics_state->gl_pos_attrib);
    glVertexAttribPointer(graphics_state->gl_pos_attrib, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    //glChk();
}