// Copyright (c) 2017 Kage authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package com.sagargv.kagegame;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;

import java.util.ArrayList;

public class Al {
    public static class AudioBuffer {
        AudioTrack mAudioTrack;
        int nFrames;
    }
    public static boolean mIsPaused = false;
    public static boolean isAudioInitialized = false;
    static ArrayList<AudioBuffer> mAudioBuffers = new ArrayList<AudioBuffer>();
    public static final int AL_PLAY_ONCE = 0;
    public static final int AL_PLAY_INFINITE = 1;

    public static int init() {
        isAudioInitialized = true;
        for(AudioBuffer audioBuffer: mAudioBuffers) {
            audioBuffer.mAudioTrack.stop();
            audioBuffer.mAudioTrack.release();
        }
        mAudioBuffers = new ArrayList<AudioBuffer>();
        return 0;
    }

    public static int bufferTrack(float[] samples) {
        short data[] = new short[samples.length];
        for(int i = 0; i < data.length; i++) {
            data[i] = (short) (samples[i] * 32768.0f);
        }
        AudioTrack audioTrack = new AudioTrack(AudioManager.STREAM_MUSIC,
                44100, AudioFormat.CHANNEL_OUT_MONO,
                AudioFormat.ENCODING_PCM_16BIT, samples.length*2,
                AudioTrack.MODE_STATIC);
        audioTrack.write(data, 0, data.length);

        AudioBuffer audioBuffer = new AudioBuffer();
        audioBuffer.mAudioTrack = audioTrack;
        audioBuffer.nFrames = data.length;

        mAudioBuffers.add(audioBuffer);
        return mAudioBuffers.size()-1;
    }

    public static void playTrack(int trackID, int mode) {
        AudioBuffer audioBuffer = mAudioBuffers.get(trackID);
        if (audioBuffer != null) {
            AudioTrack audioTrack = audioBuffer.mAudioTrack;
            if(audioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING) {
                audioTrack.stop();
            }
            if (mode == AL_PLAY_INFINITE) {
                int bufSize = audioBuffer.nFrames;
                audioTrack.setLoopPoints(0, bufSize, -1);
            } else {
                audioTrack.setLoopPoints(0, 0, 0);
            }
            audioTrack.play();
        }
    }

    public static void stopTrack(int trackID) {
        AudioBuffer audioBuffer = mAudioBuffers.get(trackID);
        if (audioBuffer != null) {
            audioBuffer.mAudioTrack.stop();
        }
    }

    public static synchronized void onPause() {
        mIsPaused = true;
        for(AudioBuffer audioBuffer: mAudioBuffers) {
            if(audioBuffer.mAudioTrack.getPlayState() == AudioTrack.PLAYSTATE_PLAYING) {
                audioBuffer.mAudioTrack.pause();
            }
        }
    }

    public static synchronized void onResume() {
        mIsPaused = false;
        for(AudioBuffer audioBuffer: mAudioBuffers) {
            if(audioBuffer.mAudioTrack.getPlayState() == AudioTrack.PLAYSTATE_PAUSED) {
                audioBuffer.mAudioTrack.play();
            }
        }
    }

    public static synchronized boolean isPaused() {
        return mIsPaused;
    }
}