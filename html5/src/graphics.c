// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include <stdlib.h>
#include <math.h>
#include <string.h>

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

int BakeFont(FontFace* font_face, const char* file_name, float font_size) {
    FILE* fp = platform_fopen(file_name, "rb");
    if (fp == NULL) {
        LOGE("Error loading font\n");
        return -1;
    }
    unsigned char* ttf_buffer = (unsigned char*) malloc(1 << 21);
    unsigned char* temp_bitmap = (unsigned char*) malloc(1024*1024);
    if (ttf_buffer == NULL || temp_bitmap == NULL) {
        LOGE("Insufficient memory to load font\n");
        return -1;
    }
    fread(ttf_buffer, 1, 1 << 21, fp);
    stbtt_BakeFontBitmap(ttf_buffer, 0, font_size, temp_bitmap, 1024, 1024, 32, 96, font_face->cdata);

    glGenTextures(1, &font_face->gl_tex);
    glBindTexture(GL_TEXTURE_2D, font_face->gl_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 1024, 1024, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free(temp_bitmap);
    free(ttf_buffer);
    platform_fclose(fp);

    return 0;
}

float sample_verts[] = {
    -0.5f, -0.5f, (512.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
    -0.5f,  0.5f, (512.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
     0.5f, -0.5f, (639.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,

     0.5f, -0.5f, (639.0f + 0.5f)/1024.0f, (127.0f + 0.5f)/1024.0f,
    -0.5f,  0.5f, (512.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
     0.5f,  0.5f, (639.0f + 0.5f)/1024.0f, (000.0f + 0.5f)/1024.0f,
};
char text[100] = "0123456789";
float text_verts[512];

int GraphicsInit(GraphicsState* graphics_state)
{
    const GLchar* vertex_src =
        "precision highp float;\n"
        "attribute vec2 a_pos;\n"
        "attribute vec2 a_tex;\n"
        "uniform mat4 u_mvp;\n"
        "varying vec2 v_tex;\n"
        "void main() {\n"
        "    gl_Position = u_mvp * vec4(a_pos.xy, 0.0, 1.0);\n"
        "    v_tex = a_tex;\n"
        "}\n";
    const GLchar* fragment_src =
        "precision highp float;\n"
        "uniform sampler2D u_sampler;\n"
        "varying vec2 v_tex;\n"
        "void main() {\n"
        "    gl_FragColor = texture2D(u_sampler, v_tex);\n"
        "}\n";
    graphics_state->gl_simple_shader = makeShaderProgram(vertex_src, fragment_src);
    graphics_state->gl_pos_attrib = glGetAttribLocation(graphics_state->gl_simple_shader, "a_pos");
    graphics_state->gl_tex_attrib = glGetAttribLocation(graphics_state->gl_simple_shader, "a_tex");
    graphics_state->gl_sampler_uniform = glGetUniformLocation(graphics_state->gl_simple_shader, "u_sampler");
    graphics_state->gl_mvp_uniform = glGetUniformLocation(graphics_state->gl_simple_shader, "u_mvp");

    glGenBuffers(1, &graphics_state->gl_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, graphics_state->gl_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sample_verts), sample_verts, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    int img_w, img_h;
    unsigned char* pixel_data = PlatformImgLoad("atlas.png", &img_w, &img_h);
    if (pixel_data == NULL) {
        LOGE("Failed to load texture image\n");
        return 1;
    }

    glGenTextures(1, &graphics_state->gl_tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, graphics_state->gl_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_w, img_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel_data);

    PlatformImgFree(pixel_data);

    ////////////////////////////////// Font ////////////////////////////////////////
    const GLchar* font_vertex_src =
        "precision highp float;\n"
        "attribute vec2 a_pos;\n"
        "attribute vec2 a_tex;\n"
        "uniform mat4 u_mvp;\n"
        "varying vec2 v_tex;\n"
        "void main() {\n"
        "    gl_Position = u_mvp * vec4(a_pos.xy, 0.0, 1.0);\n"
        "    v_tex = a_tex;\n"
        "}\n";
    const GLchar* font_fragment_src =
        "precision highp float;\n"
        "uniform sampler2D u_sampler;\n"
        "uniform vec4 u_color;\n"
        "varying vec2 v_tex;\n"
        "void main() {\n"
        "    gl_FragColor = vec4(u_color.rgb, u_color.a * texture2D(u_sampler, v_tex).a);\n"
        "}\n";
    graphics_state->font_shader.gl_program = makeShaderProgram(font_vertex_src, font_fragment_src);
    graphics_state->font_shader.gl_pos_attrib = glGetAttribLocation(graphics_state->font_shader.gl_program, "a_pos");
    graphics_state->font_shader.gl_tex_attrib = glGetAttribLocation(graphics_state->font_shader.gl_program, "a_tex");
    graphics_state->font_shader.gl_sampler_uniform = glGetUniformLocation(graphics_state->font_shader.gl_program, "u_sampler");
    graphics_state->font_shader.gl_mvp_uniform = glGetUniformLocation(graphics_state->font_shader.gl_program, "u_mvp");
    graphics_state->font_shader.gl_color_uniform = glGetUniformLocation(graphics_state->font_shader.gl_program, "u_color");

    glGenBuffers(1, &graphics_state->font_shader.gl_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, graphics_state->font_shader.gl_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(text_verts), text_verts, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if(BakeFont(&graphics_state->font, "glfont.ttf", 64.0f) != 0) {
        LOGE("Error loading font\n");
        return 1;
    }

    float x = 0.5, y = 0.75;

    float scale_factor = 250.0f;
    x *= scale_factor; y *= -scale_factor;
    stbtt_aligned_quad q;
    for(int i = 0; i < strlen(text); i++) {
        stbtt_GetBakedQuad(graphics_state->font.cdata, 1024, 1024, text[i]-32, &x, &y, &q, 1);

        // Triangle 1
        text_verts[24*i+0] = q.x0; text_verts[24*i+1] = q.y0;
        text_verts[24*i+2] = q.s0; text_verts[24*i+3] = q.t0;

        text_verts[24*i+4] = q.x1; text_verts[24*i+5] = q.y0; 
        text_verts[24*i+6] = q.s1; text_verts[24*i+7] = q.t0;

        text_verts[24*i+8] = q.x1; text_verts[24*i+9] = q.y1; 
        text_verts[24*i+10] = q.s1; text_verts[24*i+11] = q.t1;

        // Triangle 2
        text_verts[24*i+12] = q.x0; text_verts[24*i+13] = q.y1; 
        text_verts[24*i+14] = q.s0; text_verts[24*i+15] = q.t1;

        text_verts[24*i+16] = q.x0; text_verts[24*i+17] = q.y0; 
        text_verts[24*i+18] = q.s0; text_verts[24*i+19] = q.t0;

        text_verts[24*i+20] = q.x1; text_verts[24*i+21] = q.y1; 
        text_verts[24*i+22] = q.s1; text_verts[24*i+23] = q.t1;

        text_verts[24*i+0] = text_verts[24*i+0]/scale_factor; text_verts[24*i+1] = -text_verts[24*i+1]/scale_factor;
        text_verts[24*i+4] = text_verts[24*i+4]/scale_factor; text_verts[24*i+5] = -text_verts[24*i+5]/scale_factor;
        text_verts[24*i+8] = text_verts[24*i+8]/scale_factor; text_verts[24*i+9] = -text_verts[24*i+9]/scale_factor;

        text_verts[24*i+12] = text_verts[24*i+12]/scale_factor; text_verts[24*i+13] = -text_verts[24*i+13]/scale_factor;
        text_verts[24*i+16] = text_verts[24*i+16]/scale_factor; text_verts[24*i+17] = -text_verts[24*i+17]/scale_factor;
        text_verts[24*i+20] = text_verts[24*i+20]/scale_factor; text_verts[24*i+21] = -text_verts[24*i+21]/scale_factor;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    float mvp_matrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    mvp_matrix[0] = 1.0f/graphics_state->aspect_ratio;
    
    // Render a quad
    glUseProgram(graphics_state->gl_simple_shader);

    glBindBuffer(GL_ARRAY_BUFFER, graphics_state->gl_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sample_verts), NULL, GL_STREAM_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sample_verts), sample_verts, GL_STREAM_DRAW);

    glVertexAttribPointer(graphics_state->gl_pos_attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glEnableVertexAttribArray(graphics_state->gl_pos_attrib);
    glVertexAttribPointer(graphics_state->gl_tex_attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(graphics_state->gl_tex_attrib);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, graphics_state->gl_tex);
    glUniform1i(graphics_state->gl_sampler_uniform, 0);

    glUniformMatrix4fv(graphics_state->gl_mvp_uniform, 1, GL_FALSE, mvp_matrix);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Render Text
    glUseProgram(graphics_state->font_shader.gl_program);

    glBindBuffer(GL_ARRAY_BUFFER, graphics_state->font_shader.gl_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(text_verts), NULL, GL_STREAM_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(text_verts), text_verts, GL_STREAM_DRAW);

    glVertexAttribPointer(graphics_state->font_shader.gl_pos_attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glEnableVertexAttribArray(graphics_state->font_shader.gl_pos_attrib);
    glVertexAttribPointer(graphics_state->font_shader.gl_tex_attrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(graphics_state->font_shader.gl_tex_attrib);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, graphics_state->font.gl_tex);
    glUniform1i(graphics_state->font_shader.gl_sampler_uniform, 0);

    glUniformMatrix4fv(graphics_state->font_shader.gl_mvp_uniform, 1, GL_FALSE, mvp_matrix);
    glUniform4f(graphics_state->font_shader.gl_color_uniform, 0.5f, 0.0f, 0.0f, 1.0f);

    glDrawArrays(GL_TRIANGLES, 0, 6*strlen(text));
    
    //glChk();
}