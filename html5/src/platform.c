// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

#include <stdlib.h>
#include <emscripten/emscripten.h>

#define GLFW_INCLUDE_ES2
#include <GLFW/glfw3.h>

#include "platform.h"
#include "game.h"

int width, height;
GLFWwindow* window;

GameState *game_state;

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

    GameStateUpdate(game_state, game_input);
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
    GameInit(game_state);

    LOGI("Starting main loop\n");
    emscripten_set_main_loop(loop, 0, 1);

    return 0;
}