#ifndef ANDROIDFILEIO_H_
#define ANDROIDFILEIO_H_

#include <jni.h>
#include "../Interfaces/IFileIO.h"

class AAssetManager;
class AndroidFileIO : public IFileIO {
public:
	AndroidFileIO( JNIEnv* env, jobject assetManager );
	~AndroidFileIO();

	IFile* ReadStorage( const char* fileName ) const;
	IFile* WriteStorage( const char* fileName ) const;

	IFile* ReadAsset( const char* fileName ) const;

private:
	AAssetManager* mAssetManager;
};

#endif /* ANDROIDFILEIO_H_ */
