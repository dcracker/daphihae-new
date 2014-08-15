package com.summoner.daphihae;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends Activity implements SurfaceHolder.Callback {
	
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		// make full screen
		requestWindowFeature( Window.FEATURE_NO_TITLE );
		getWindow().setFlags( WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN );
		
		// init surface
		SurfaceView view = new MySurfaceView( this );
		view.getHolder().addCallback( this );
		setContentView( view );
		
		// start game
		NativeInterface.OnCreate( getAssets(), getApplicationContext().getFilesDir().toString() );
	}
	
	@Override
	public void onResume() {
		super.onResume();
		NativeInterface.OnResume();
	}
	
	@Override
	public void onPause() {
		super.onPause();
		NativeInterface.OnPause();
	}
	
	@Override
	public void onDestroy() {
		super.onDestroy();
		NativeInterface.OnDestroy();
	}

// SurfaceHolder.Callback methods
	@Override
	public void surfaceChanged( SurfaceHolder holder, int format, int w, int h ) {
		NativeInterface.OnSurfaceChanged( holder.getSurface() );
	}

	@Override
	public void surfaceCreated( SurfaceHolder holder ) {
		// do nothing
	}

	@Override
	public void surfaceDestroyed( SurfaceHolder holder ) {
		NativeInterface.OnSurfaceChanged( null );
		
	}
	
	private class MySurfaceView extends SurfaceView {
		public MySurfaceView( Context context ) {
			super( context );
			setFocusable( true );
		}

		@Override
		public boolean onTouchEvent( MotionEvent event ) {
			int action = event.getActionMasked();
			int pointerIndex = event.getActionIndex();
			int pointerId = event.getPointerId( pointerIndex );
			
			switch ( action ) {
			case MotionEvent.ACTION_DOWN:
			case MotionEvent.ACTION_POINTER_DOWN:
				NativeInterface.OnTouch( 0, pointerId, (int)(event.getX( pointerIndex )), (int)(event.getY( pointerIndex )) );
				break;
			
			case MotionEvent.ACTION_CANCEL:
			case MotionEvent.ACTION_UP:
			case MotionEvent.ACTION_POINTER_UP:
				NativeInterface.OnTouch( 1, pointerId, (int)(event.getX( pointerIndex )), (int)(event.getY( pointerIndex )) );
				break;
				
			case MotionEvent.ACTION_MOVE:
				int pointerCount = event.getPointerCount();
				for ( int i=0; i < pointerCount; ++i ) {
					NativeInterface.OnTouch( 2, pointerId, (int)(event.getX( pointerIndex )), (int)(event.getY( pointerIndex )) );
				}
				break;
			}
			return true;
		}
	}
	
	static {
		System.loadLibrary("nativeImpl");
	}
	
}
