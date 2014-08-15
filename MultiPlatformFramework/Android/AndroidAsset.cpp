#include "stdafx.h"
#include "AndroidAsset.h"

#include <android/asset_manager.h>

#include "logger.h"
#define LOG_TAG "File"

AndroidAsset::AndroidAsset( AAssetManager* mgr, const char* fileName )
	: mAssetFile( NULL )
	, cFileName( fileName )
{
	mAssetFile = AAssetManager_open( mgr, fileName, AASSET_MODE_UNKNOWN );
	if ( mAssetFile == NULL ) {
		LOG_ERROR( "cannot read asset : %s", fileName );
	}
}

AndroidAsset::~AndroidAsset() {
	Close();
}

bool AndroidAsset::ReadByte( void* out_byteBuffer, int numBytesToRead ) {
	int numBytesHasRead = AAsset_read( mAssetFile, out_byteBuffer, numBytesToRead );
	return (numBytesHasRead == numBytesToRead);
}

void AndroidAsset::Close() {
	AAsset_close( mAssetFile );
	mAssetFile = NULL;
}
