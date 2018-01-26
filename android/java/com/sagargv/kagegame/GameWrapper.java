// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package com.sagargv.kagegame;

public class GameWrapper {
    static {
        System.loadLibrary("kage");
    }

    public static native void setDataDir(String dataDir);

    public static native int getGameStateSize();
    public static native byte[] getGameState();
    public static native void setGameState(byte[] gameState);

    public static native int audioInit();
    public static native int graphicsInit();

    public static native void gameReset();
    public static native void gameLoop(int width, int height, int eventType, float x, float y);
}