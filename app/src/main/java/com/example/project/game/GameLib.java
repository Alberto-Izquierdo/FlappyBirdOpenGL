package com.example.project.game;

/**
 * Created by Alberto on 15/02/2018.
 */

public class GameLib {
	private static TextureLoader textureLoader;

    static{
        System.loadLibrary("game");
    }

    public static native void init();
    public static native void resize(int width, int height);
    public static native void step();
    public static native boolean touch();
    public static int LoadTexture(String path)
    {
        return textureLoader.LoadTexture(path);
    }

	public static void SetTextureLoader(TextureLoader texLoader)
	{
		textureLoader = texLoader;
	}
}
