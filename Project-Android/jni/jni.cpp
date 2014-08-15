#include "stdafx.h"

#include <jni.h>
#include <android/native_window.h> // requires ndk r5 or newer
#include <android/native_window_jni.h> // requires ndk r5 or newer

#include "Common/MainGameLoop.h"
#include "Common/CommonTouchMessageHandler.h"
#include "AndroidPlatform.h"
#include "AndroidTimer.h"
#include "DaPhiHae.h"
#ifndef NDEBUG
#include <unistd.h>
#endif

#define JNI_METHOD( methodName ) \
	Java_com_summoner_daphihae_NativeInterface_##methodName
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
static CommonTouchMessageHandler* touchHandler;

IMPL_JNI_API_WITH_PARAM( OnCreate, jobject assetManager, jstring dataRoot ) {
#ifndef NDEBUG
//usleep(5000 * 1000);	// wait for debuger attach.
#endif
	const char* dataRootPath = env->GetStringUTFChars( dataRoot , NULL );
	LOG_INFO( "NativeOnStart()" );
	touchHandler = new CommonTouchMessageHandler();
	platform = new AndroidPlatform( env, assetManager, dataRootPath, touchHandler );
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
	LOG_INFO( "TouchEvent %d, %d, %d, %d", eventType, pointerId, x, y );
	touchHandler->ProcessTouchInput( (TouchEventType)eventType, pointerId, x, y );
}

} // extern "C"
