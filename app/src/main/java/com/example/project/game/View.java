package com.example.project.game;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by Alberto on 14/02/2018.
 */

public class View extends GLSurfaceView {

    static{
        System.loadLibrary("game");
    }

    public View(Context context) {
        super(context);
        setEGLConfigChooser(8, 8, 8, 0, 16, 0);
        setEGLContextClientVersion(2);
        setRenderer(new Renderer());
    }

    private static class Renderer implements GLSurfaceView.Renderer{

        @Override
        public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
            GameLib.init();
        }

        @Override
        public void onSurfaceChanged(GL10 gl10, int width, int height) {
            GameLib.resize(width, height);
        }

        @Override
        public void onDrawFrame(GL10 gl10) {
            GameLib.step();
        }

    }

    @Override
    public boolean onTouchEvent(MotionEvent e) {
        GameLib.touch();
        return true;
    }
}