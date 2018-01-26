// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <jni.h>

#include "platform.h"
#include "game.h"
#include "graphics.h"
#include "audio.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GameState* game_state;
char dataDirPath[250];
int width, height;
JNIEnv *g_env;
int ch;

JNIEXPORT void JNICALL Java_com_sagargv_kagegame_GameWrapper_setDataDir
    (JNIEnv *env, jclass this, jstring dataDir_)
{
    g_env = env;
    const char *dataDir = (*env)->GetStringUTFChars(env, dataDir_, 0);
    strcpy(dataDirPath, dataDir);
}

JNIEXPORT jint JNICALL Java_com_sagargv_kagegame_GameWrapper_gameInit
    (JNIEnv *env, jclass this, jbyteArray jGameState)
{
    g_env = env;
    GameState* game_state = (GameState*)(*env)->GetByteArrayElements(env, jGameState, NULL);
    //game_state = (GameState*) calloc(1, sizeof(GameState));
    int res = GameInit(game_state);
    (*env)->ReleaseByteArrayElements(env, jGameState, (jbyte*)game_state, JNI_ABORT);
    return res;
}

JNIEXPORT void JNICALL Java_com_sagargv_kagegame_GameWrapper_gameReset
    (JNIEnv *env, jclass this, jbyteArray jGameState)
{
    g_env = env;
    GameState* game_state = (GameState*)(*env)->GetByteArrayElements(env, jGameState, NULL);
    GameReset(game_state);
    (*env)->ReleaseByteArrayElements(env, jGameState, (jbyte*)game_state, JNI_ABORT);
}


JNIEXPORT void JNICALL Java_com_sagargv_kagegame_GameWrapper_gameLoop
    (JNIEnv *env, jclass this, jbyteArray jGameState, jint event_idx, jfloat x, jfloat y)
{
    g_env = env;
    GameState* game_state = (GameState*)(*env)->GetByteArrayElements(env, jGameState, NULL);
    GameInputEventType event_type = GAME_INPUT_EVENT_NULL;
    if(event_idx == 1) {
        event_type = GAME_INPUT_EVENT_SWIPE_UP;
    }
    if(event_idx == 2) {
        event_type = GAME_INPUT_EVENT_SWIPE_DOWN;
    }
    if(event_idx == 3) {
        event_type = GAME_INPUT_EVENT_SWIPE_LEFT;
    }
    if(event_idx == 4) {
        event_type = GAME_INPUT_EVENT_SWIPE_RIGHT;
    }
    if(event_idx == 5) {
        event_type = GAME_INPUT_EVENT_PRESS;
    }
    if(event_idx == 6) {
        event_type = GAME_INPUT_EVENT_PAUSE;
    }
    GameInput game_input = {event_type, x, y};
    GameStateUpdate(game_state, game_input);
    GameRender(game_state);
    (*env)->ReleaseByteArrayElements(env, jGameState, (jbyte*)game_state, JNI_ABORT);
}

unsigned char* PlatformImgLoad(const char* fileName, int* width, int* height)
{
    int n;
    char imgPath[1000];
    sprintf(imgPath, "%s/%s", dataDirPath, fileName);
    return stbi_load(imgPath, width, height, &n, 4);
}

void PlatformImgFree(unsigned char* data)
{
    stbi_image_free(data);
}

FILE* platform_fopen(const char* fileName, const char* mode)
{
    char filePath[250];
    sprintf(filePath, "%s/%s", dataDirPath, fileName);
    return fopen(filePath, mode);
}

void platform_fclose(FILE* fp)
{
    fclose(fp);
}