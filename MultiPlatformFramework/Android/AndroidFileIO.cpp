#include "stdafx.h"
#include "AndroidFileIO.h"

#include <android/asset_manager_jni.h>
#include "AndroidAsset.h"


AndroidFileIO::AndroidFileIO( JNIEnv* env, jobject assetManager )
	: mAssetManager( AAssetManager_fromJava( env, assetManager ) )
{
}

AndroidFileIO::~AndroidFileIO() {
	mAssetManager = NULL;
}


IFile* AndroidFileIO::ReadStorage( const char* fileName ) const {
	return NULL;
}

IFile* AndroidFileIO::WriteStorage( const char* fileName ) const {
	return NULL;
}

IFile* AndroidFileIO::ReadAsset( const char* fileName ) const {
	return new AndroidAsset( mAssetManager, fileName );
}
