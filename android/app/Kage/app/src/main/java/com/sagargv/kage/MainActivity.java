package com.sagargv.kage;

import android.content.res.AssetManager;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.os.Environment;
import android.support.v4.view.GestureDetectorCompat;
import android.support.v4.view.MotionEventCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Display;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Toast;

import com.sagargv.kagegame.GameWrapper;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends AppCompatActivity implements GLSurfaceView.Renderer, GestureDetector.OnGestureListener {
    private GLSurfaceView mGLView;
    int mWidth, mHeight;
    private GestureDetectorCompat mDetector;

    byte[] mGameState;

    int mEvent;
    float mEventX, mEventY;
    private long mLastEventTime;
    private long mLastFrameTime;

    public class GameInputEventType {
        public static final int NULL = 0;
        public static final int SWIPE_UP = 1;
        public static final int SWIPE_DOWN = 2;
        public static final int SWIPE_LEFT = 3;
        public static final int SWIPE_RIGHT = 4;
        public static final int PAUSE = 5;
        public static final int PRESS = 6;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // setContentView(R.layout.activity_main);

        supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

        mGameState = new byte[1024*1024]; // 2 MB for game state

        mGLView = new GLSurfaceView(this);
        mGLView.setEGLContextClientVersion(2);
        mGLView.setRenderer(this);
        setContentView(mGLView);

        mDetector = new GestureDetectorCompat(this, this);

        File dataDir = getExternalFilesDir(null);
        if (Environment.MEDIA_MOUNTED.equals(Environment.getExternalStorageState()) && dataDir != null) {
            GameWrapper.setDataDir(dataDir.getAbsolutePath());
        }
        else {
            Log.e("TAG", "Unable to write game assets to SD card");
            return;
        }

        extractAssets(); // extract compressed assets from APK to SD card (virtual)
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        mDetector.onTouchEvent(event);
        return super.onTouchEvent(event);
    }

    @Override
    public boolean onDown(MotionEvent e) {
        return false;
    }

    @Override
    public void onShowPress(MotionEvent e) {

    }

    @Override
    public boolean onSingleTapUp(MotionEvent e) {
        float pctX = e.getX() / mWidth;
        float pctY = e.getY() / mHeight;
        if(pctX > 0.9 && pctY < 0.1) {
            mEvent = GameInputEventType.PAUSE;
        }
        else {
            mEvent = GameInputEventType.PRESS;
        }
        mEventX = 0;
        mEventY = 0;
        mLastEventTime = e.getEventTime();
        return true;
    }

    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
        if(e1.getEventTime() != mLastEventTime) {
            if(Math.abs(distanceX) > 5 || Math.abs(distanceY) > 5) {
                if(Math.abs(distanceX) > Math.abs(distanceY)) {
                    mEvent = (distanceX < 0) ? GameInputEventType.SWIPE_RIGHT : GameInputEventType.SWIPE_LEFT;
                }
                else {
                    mEvent = (distanceY < 0) ? GameInputEventType.SWIPE_DOWN : GameInputEventType.SWIPE_UP;
                }
                mEventX = 0;
                mEventY = 0;
                mLastEventTime = e1.getEventTime();
            }
        }
        return false;
    }

    @Override
    public void onLongPress(MotionEvent e) {

    }

    @Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        return false;
    }

    @Override
    protected void onPause() {
        super.onPause();
        mEvent = GameInputEventType.PAUSE;
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        final int res = GameWrapper.gameInit(mGameState);
        if (res != 0) {
            finish();
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(getApplicationContext(), "Rendering error (code " + res + ")", Toast.LENGTH_SHORT).show();
                }
            });
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        mWidth = width;
        mHeight = height;
        GLES20.glViewport(0, 0, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        int ev = mEvent;
        mEvent = GameInputEventType.NULL;
        GameWrapper.gameLoop(mGameState, ev, mEventX, mEventY);
    }

    private void extractAssets() {
        AssetManager assetManager = getAssets();
        String[] files = null;
        try {
            files = assetManager.list("");
        } catch (IOException e) {
            Log.e("TAG", "Failed to get asset file list.", e);
        }
        if (files != null) for (String filename : files) {
            if (filename.contains(".")) {
                InputStream in = null;
                OutputStream out = null;
                try {
                    in = assetManager.open(filename);
                    File outFile = new File(getExternalFilesDir(null), filename);
                    out = new FileOutputStream(outFile);
                    copyFile(in, out);
                } catch (IOException e) {
                    e.printStackTrace();
                    Log.e("TAG", "Failed to copy asset file: " + filename, e);
                } finally {
                    if (in != null) {
                        try {
                            in.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                    if (out != null) {
                        try {
                            out.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }
        }
    }

    private void copyFile(InputStream in, OutputStream out) throws IOException {
        byte[] buffer = new byte[1024];
        int read;
        while ((read = in.read(buffer)) != -1) {
            out.write(buffer, 0, read);
        }
    }
}
