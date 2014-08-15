package com.summoner.daphihae;

import android.content.res.AssetManager;
import android.util.Log;
import android.view.Surface;

public class NativeInterface {
	// native methods
	public native static void OnCreate( AssetManager assetManager, String dataRoot );
	public native static void OnResume();
	public native static void OnPause();
	public native static void OnDestroy();
	
	public native static void OnSurfaceChanged( Surface surface );
	public native static void OnTouch( int eventType, int pointerId, int x, int y );
	
	public static void TestCallFromCpp() {
		Log.d("JNI Test", "Calls from cpp");
	}
}
