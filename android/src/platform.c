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

GameState game_state;
char dataDirPath[250];
int width, height;
JNIEnv *g_env;
jclass g_clazz;


JNIEXPORT void JNICALL Java_com_sagargv_kage_GameWrapper_setDataDir
        (JNIEnv *env, jclass this, jstring dataDir_)
{
    g_env = env;
    const char *dataDir = (*env)->GetStringUTFChars(env, dataDir_, 0);
    strcpy(dataDirPath, dataDir);
}



JNIEXPORT jint JNICALL Java_com_sagargv_kage_GameWrapper_getGameStateSize
        (JNIEnv *env, jclass this)
{
    g_env = env;
    return sizeof(GameState);
}

JNIEXPORT jbyteArray JNICALL Java_com_sagargv_kage_GameWrapper_getGameState
        (JNIEnv *env, jclass this)
{
    g_env = env;
    jbyteArray jbuf = (*env)->NewByteArray(env, sizeof(GameState));
    (*env)->SetByteArrayRegion(env, jbuf, 0, sizeof(GameState), (const jbyte *)&game_state);
    return jbuf;
}

JNIEXPORT void JNICALL Java_com_sagargv_kage_GameWrapper_setGameState
        (JNIEnv *env, jclass this, jbyteArray jGameState)
{
    g_env = env;
    jbyte* jbuffer = (*env)->GetByteArrayElements(env, jGameState, NULL);
    unsigned char* game_state_ptr = (unsigned char*) &game_state;
    int i;
    for(i = 0; i < sizeof(GameState); i++) {
        game_state_ptr[i] = jbuffer[i];
    }
    (*env)->ReleaseByteArrayElements(env, jGameState, jbuffer, JNI_ABORT);
}

JNIEXPORT jint JNICALL Java_com_sagargv_kage_GameWrapper_audioInit
        (JNIEnv *env, jclass this)
{
    g_env = env;
    return AudioInit(&game_state);
}

JNIEXPORT jint JNICALL Java_com_sagargv_kage_GameWrapper_graphicsInit
        (JNIEnv *env, jclass this)
{
    g_env = env;
    return GraphicsInit(&game_state);
}

JNIEXPORT void JNICALL Java_com_sagargv_kage_GameWrapper_gameReset
        (JNIEnv *env, jclass this)
{
    g_env = env;
    GameReset(&game_state);
}


JNIEXPORT void JNICALL Java_com_sagargv_kage_GameWrapper_gameLoop
(JNIEnv *env, jclass this, jint w, jint h, jint event_idx, jfloat x, jfloat y)
{
    g_env = env;
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
    GameStateUpdate(&game_state, game_input);
    GameRender(&game_state);
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