#ifndef ANDROIDASSET_H_
#define ANDROIDASSET_H_

#include "IFile.h"

class AAssetManager;
class AAsset;
class AndroidAsset : public IFile {
public:
	AndroidAsset( AAssetManager* mgr, const char* fileName );
	~AndroidAsset();

	const char* GetFileName() { return cFileName; }
	bool ReadByte( void* out_byteBuffer, int numByteToRead );

private:
	const char* const cFileName;
	AAsset* mAssetFile;
};

#endif /* ANDROIDASSET_H_ */
