#ifndef ANDROIDFILEIO_H_
#define ANDROIDFILEIO_H_

#include <jni.h>
#include "../Common/CommonFileIO.h"

class AAssetManager;
class AndroidFileIO : public CommonFileIO {
public:
	AndroidFileIO( JNIEnv* env, jobject assetManager, const char* dataRoot );
	~AndroidFileIO();

	IFileReader* ReadAsset( const char* fileName ) const;

private:
	AAssetManager* mAssetManager;
};

#endif /* ANDROIDFILEIO_H_ */
