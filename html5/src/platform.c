// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include <stdlib.h>
#include <emscripten/emscripten.h>

#define GLFW_INCLUDE_ES2
#include <GLFW/glfw3.h>

#include "platform.h"

GLFWwindow* window;

void loop()
{
    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
}

int main()
{
    if (!glfwInit()) {
        LOGE("GLFW Init failed\n");
        return 1;
    }

    int width = 960, height = 540;
    glfwWindowHint(GLFW_SAMPLES, 4);
    window = glfwCreateWindow(width, height, "Kage", NULL, NULL);
    if (!window)
    {
        LOGE("GLFW Window Creation failed\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    
    LOGI("Starting main loop\n");
    emscripten_set_main_loop(loop, 0, 1);

    return 0;
}