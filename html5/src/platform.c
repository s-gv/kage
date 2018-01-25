// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdlib.h>
#include <emscripten/emscripten.h>

#include "platform.h"
#include "game.h"

#define GLFW_INCLUDE_ES2
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int width, height;
GLFWwindow* window;

GameState *game_state;
double last_frame_time, acc;
double last_tick;

void loop()
{
    GameInputEventType event_type = GAME_INPUT_EVENT_NULL;
    float x = 0, y = 0;

    glfwPollEvents();
    if((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) ||
        (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)) {
        event_type = GAME_INPUT_EVENT_SWIPE_UP;
    }
    if((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) ||
         (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)) {
        event_type = GAME_INPUT_EVENT_SWIPE_DOWN;
    }
    if((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) ||
         (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)) {
        event_type = GAME_INPUT_EVENT_SWIPE_LEFT;
    }
    if((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) ||
         (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)) {
        event_type = GAME_INPUT_EVENT_SWIPE_RIGHT;
    }
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        event_type = GAME_INPUT_EVENT_PAUSE;
    }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        event_type = GAME_INPUT_EVENT_PRESS;
        double xd, yd;
        glfwGetCursorPos(window, &xd, &yd);
        x = (float) (xd/width);
        y = (float) (yd/height);
    }
    GameInput game_input = {event_type, x, y};

    double t = emscripten_get_now();
    double dt = (t - last_frame_time);
    last_frame_time = t;
    
    // if(t < 12000) LOGI("Frame time: %.2f\n", dt);

    int n_ticks = 0;
    while(dt > GAME_TICK_MS/2) {
        GameStateUpdate(game_state, game_input);
        n_ticks++;
        if(n_ticks > 3) {
            break;
        }
        dt -= GAME_TICK_MS;
    }
    GameRender(game_state);
    glfwSwapBuffers(window);
}

int main()
{
    if (!glfwInit()) {
        LOGE("GLFW Init failed\n");
        return 1;
    }

    // emscripten_get_canvas_size(&width, &height, NULL);
    width = 960; height = 540; // Force window size
    LOGI("Window size -- w: %d, h: %d\n", width, height);

    glfwWindowHint(GLFW_SAMPLES, 4);
    window = glfwCreateWindow(width, height, "Kage", NULL, NULL);
    if (!window)
    {
        LOGE("GLFW Window Creation failed\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    game_state = (GameState*) calloc(1, sizeof(GameState));
    if(GameInit(game_state) != 0) {
        LOGE("Game init failed.\n");
        return -1;
    }
    game_state->aspect_ratio = (width*1.0f)/height;

    LOGI("Starting main loop.\n");
    emscripten_set_main_loop(loop, 0, 1);

    return 0;
}

unsigned char* PlatformImgLoad(const char* fileName, int* width, int* height)
{
    int n;
    char filePath[1000];
    sprintf(filePath, "asset/%s", fileName);
    return stbi_load(filePath, width, height, &n, 4);
}

void PlatformImgFree(unsigned char* data)
{
    stbi_image_free(data);
}

FILE* platform_fopen(const char* fileName, const char* mode)
{
    char filePath[250];
    sprintf(filePath, "asset/%s", fileName);
    return fopen(filePath, mode);
}

void platform_fclose(FILE* fp)
{
    fclose(fp);
}