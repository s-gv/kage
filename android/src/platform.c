// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <jni.h>
#include <time.h>

#include "platform.h"
#include "game.h"
#include "graphics.h"
#include "audio.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GameState* game_state;
char dataDirPath[250];
JNIEnv *g_env;
struct timespec last_frame_time;

struct timespec diff(struct timespec start, struct timespec end)
{
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

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
        event_type = GAME_INPUT_EVENT_PAUSE;
    }
    if(event_idx == 6) {
        event_type = GAME_INPUT_EVENT_PRESS;
    }
    /*
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    struct timespec delta = diff(last_frame_time, now);
    float dt = delta.tv_nsec / 1e6;
    if(dt > GAME_TICK_MS/2) {
        last_frame_time = now;
    }
    while(dt > GAME_TICK_MS/2) {
        event_type = GAME_INPUT_EVENT_NULL; x = 0; y = 0;
        dt -= GAME_TICK_MS;
    }
    */
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