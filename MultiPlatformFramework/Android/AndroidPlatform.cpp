#include "stdafx.h"
#include "AndroidPlatform.h"
#include "AndroidGraphics.h"
#include "AndroidInput.h"
#include "AndroidFileIO.h"

#include <unistd.h>			// sleep

#include "logger.h"
#define LOG_TAG "Test"

AndroidPlatform::AndroidPlatform( JNIEnv* env, jobject assetManager, const CommonTouchMessageHandler* touchHandler )
	: mGraphics( new AndroidGraphics() )
	, mInput( new AndroidInput( touchHandler ) )
	, mFileIO( new AndroidFileIO( env, assetManager ) )
	, mJavaVM( NULL )
	, mJniEnv( NULL )
{
	env->GetJavaVM( &mJavaVM );
}

AndroidPlatform::~AndroidPlatform() {

	if ( mGraphics != 0 ) {
		delete mGraphics;
		mGraphics = 0;
	}
}

const IGraphics* AndroidPlatform::GetGraphics() const {
	return mGraphics;
}

IInput* AndroidPlatform::GetInput() const {
	return mInput;
}

const IFileIO* AndroidPlatform::GetFileIO() const {
	return mFileIO;
}

void AndroidPlatform::OnWindowChanged( void* args ) {
	mGraphics->SetWindow( (ANativeWindow*)args );
}

void AndroidPlatform::OnResume() {
	mJavaVM->AttachCurrentThread( &mJniEnv, NULL );
	if ( mJniEnv == NULL ) {
		LOG_INFO( "Cannot attach thread" );
	}
	LOG_INFO( "Successfully attach thread" );
	mGraphics->InitializeEGLContext();

}

void AndroidPlatform::OnPause() {
	mGraphics->DestroyEGLContext();
	mJavaVM->DetachCurrentThread();
}

void AndroidPlatform::OnPresent() const {
	mGraphics->Present();
}

void AndroidPlatform::OnTakeABreak() const {
	sleep(0);
}
