#include "stdafx.h"

#include <jni.h>
#include <android/native_window.h> // requires ndk r5 or newer
#include <android/native_window_jni.h> // requires ndk r5 or newer

#include "Common/MainGameLoop.h"
#include "AndroidPlatform.h"
#include "AndroidTimer.h"
#include "DaPhiHae.h"
#ifndef NDEBUG
#include <unistd.h>
#endif

#define JNI_METHOD( methodName ) \
	Java_com_summoner_multiplatformtest_1android_NativeInterface_##methodName
#define IMPL_JNI_API( methodName ) \
	void JNI_METHOD(methodName)( JNIEnv* env, jclass javaThis )
#define IMPL_JNI_API_WITH_PARAM( methodName, ... ) \
	void JNI_METHOD(methodName)( JNIEnv* env, jclass javaThis, __VA_ARGS__ )

#include "logger.h"
#define LOG_TAG "JNI"

extern "C" {
static ANativeWindow *window = 0;
static MainGameLoop *loop = 0;
static AndroidPlatform*	platform = NULL;
static DaPhiHae*	game = NULL;

IMPL_JNI_API_WITH_PARAM( OnCreate, jobject assetManager ) {
#ifndef NDEBUG
//usleep(5000 * 1000);	// wait for debuger attach.
#endif
	LOG_INFO( "NativeOnStart()" );
	platform = new AndroidPlatform( env, assetManager );
	game = new DaPhiHae( platform );
	loop = new MainGameLoop( game, platform, new AndroidTimer() );
}

IMPL_JNI_API( OnResume ) {
	LOG_INFO( "NativeOnResume()" );
	loop->Start();
}

IMPL_JNI_API( OnPause ) {
	LOG_INFO( "NativeOnPause()" );
	loop->Stop();
}

IMPL_JNI_API( OnDestroy ) {
	LOG_INFO( "NativeOnDestroy()" );

	delete loop;
	loop = 0;

	delete game;
	game = NULL;

	delete platform;
	platform = NULL;
}

IMPL_JNI_API_WITH_PARAM( OnSurfaceChanged, jobject surface ) {
	if (surface != 0) {
		window = ANativeWindow_fromSurface(env, surface);
		LOG_INFO( "Got window %p", window );
		loop->PushMessage( MainGameLoop::MSG_WINDOW_SET, (void*)window );
	}
	else {
		LOG_INFO( "Releasing window" );
		loop->PushMessage( MainGameLoop::MSG_WINDOW_SET, (void*)NULL );
		ANativeWindow_release( window );
	}
}

IMPL_JNI_API_WITH_PARAM( OnTouch, jint eventType, jint pointerId, jint x, jint y  ) {
	int* touchParams = new int[4];
	touchParams[0] = eventType;
	touchParams[1] = pointerId;
	touchParams[2] = x;
	touchParams[3] = y;

	LOG_INFO( "TouchEvent %d, %d, %d, %d", eventType, pointerId, x, y );
	loop->PushMessage( MainGameLoop::MSG_TOUCH_EVENT, (void*)touchParams );
}

} // extern "C"
