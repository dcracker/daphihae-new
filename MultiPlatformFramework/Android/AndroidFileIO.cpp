#include "stdafx.h"
#include "AndroidFileIO.h"

#include <android/asset_manager_jni.h>
#include "AndroidAsset.h"

AndroidFileIO::AndroidFileIO( JNIEnv* env, jobject assetManager, const char* dataRoot )
	: CommonFileIO( NULL, dataRoot, NULL )
	, mAssetManager( AAssetManager_fromJava( env, assetManager ) )
{
}

AndroidFileIO::~AndroidFileIO() {
	mAssetManager = NULL;
}

IFileReader* AndroidFileIO::ReadAsset( const char* fileName ) const {
	return new AndroidAsset( mAssetManager, fileName );
}
