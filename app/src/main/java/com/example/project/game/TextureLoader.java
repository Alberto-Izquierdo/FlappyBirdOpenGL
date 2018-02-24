package com.example.project.game;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLUtils;
import android.util.Log;

import java.io.File;
import java.io.FileInputStream;
import java.nio.ByteBuffer;

import javax.microedition.khronos.opengles.GL10;

public class TextureLoader {
	private static Activity activity;
	
	public TextureLoader(Activity act) {
		activity = act;
	}
	public static int LoadTexture (String path) {
		Bitmap bitmap = null;
		try {
			String str = path;

			File file = new File(activity.getExternalFilesDir(null), str);

			if (file.canRead())
			{
				bitmap = BitmapFactory.decodeStream(new FileInputStream(file));
			}
			else {
				bitmap = BitmapFactory.decodeStream(activity.getResources().getAssets().open(path));
			}
		}
		catch (Exception e) {
			Log.w("TextureLoader", "Could not load a file: " + path);
			return -1;
		}

		if (bitmap != null) {
			GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmap, 0);
		}
		int width = bitmap.getWidth();
		int height = bitmap.getHeight();
		int iBytes = bitmap.getWidth() * bitmap.getHeight() * 4;
		ByteBuffer buffer = ByteBuffer.allocateDirect(iBytes);
		bitmap.copyPixelsToBuffer(buffer);
		int texID[];
		texID = new int[1];
		GLES20.glGenTextures(1, texID, 0);
		GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, texID[0]);
		GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
		GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
		GLES20.glTexImage2D(GLES20.GL_TEXTURE_2D, 0, GLES20.GL_RGBA4, width, height, 0, GLES20.GL_RGBA, GLES20.GL_UNSIGNED_BYTE, buffer);
		bitmap.recycle();
		return texID[0];
	}
}
