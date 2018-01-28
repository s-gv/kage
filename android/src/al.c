// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <jni.h>
#include "audio.h"
#include "platform.h"

extern JNIEnv *g_env;

int alInit()
{
    return 0;
}

int alBufferData(int n_channels, int sample_rate, float* data, int data_count)
{
    //TODO: implement different sample rates and support more than one channel
    jclass clazz = (*g_env)->FindClass(g_env, "com/sagargv/kagegame/Al");
    jmethodID method_bufferTrack = (*g_env)->GetStaticMethodID(g_env, clazz, "bufferTrack", "([F)I");

    jfloatArray jbuf = (*g_env)->NewFloatArray(g_env, data_count);
    (*g_env)->SetFloatArrayRegion(g_env, jbuf, 0, data_count, data);
    int res = (*g_env)->CallStaticIntMethod(g_env, clazz, method_bufferTrack, jbuf);
    return res;
}

void alDestroyBuffer(int buffer)
{

}

int alPlay(int buffer, int mode)
{
    jclass clazz = (*g_env)->FindClass(g_env, "com/sagargv/kagegame/Al");
    jmethodID method_playTrack = (*g_env)->GetStaticMethodID(g_env, clazz, "playTrack", "(II)V");

    (*g_env)->CallStaticVoidMethod(g_env, clazz, method_playTrack, buffer, mode);
    return buffer;
}

void alStop(int source)
{
    jclass clazz = (*g_env)->FindClass(g_env, "com/sagargv/kagegame/Al");
    jmethodID method_stopTrack = (*g_env)->GetStaticMethodID(g_env, clazz, "stopTrack", "(I)V");
    (*g_env)->CallStaticVoidMethod(g_env, clazz, method_stopTrack, source);
}

void alResume()
{
    jclass clazz = (*g_env)->FindClass(g_env, "com/sagargv/kagegame/Al");
    jmethodID method_resume = (*g_env)->GetStaticMethodID(g_env, clazz, "onResume", "()V");
    (*g_env)->CallStaticVoidMethod(g_env, clazz, method_resume);
}

void alSuspend()
{
    jclass clazz = (*g_env)->FindClass(g_env, "com/sagargv/kagegame/Al");
    jmethodID method_suspend = (*g_env)->GetStaticMethodID(g_env, clazz, "onPause", "()V");
    (*g_env)->CallStaticVoidMethod(g_env, clazz, method_suspend);
}