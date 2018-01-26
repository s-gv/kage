// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package com.sagargv.kagegame;

public class GameWrapper {
    static {
        System.loadLibrary("kage");
    }

    public static native void setDataDir(String dataDir);

    public static native int gameInit(byte[] gameState);
    public static native void gameReset(byte[] gameState);
    public static native void gameLoop(byte[] gameState, int eventType, float x, float y);
}