#ifndef ANDROIDASSET_H_
#define ANDROIDASSET_H_

#include "Interfaces/IFileReader.h"

class AAssetManager;
class AAsset;
class AndroidAsset : public IFileReader {
public:
	AndroidAsset( AAssetManager* mgr, const char* fileName );
	~AndroidAsset();

	const char* GetFileName() const { return cFileName; }
	void Close();
	bool ReadByte( void* out_byteBuffer, int numByteToRead );

private:
	const char* const cFileName;
	AAsset* mAssetFile;
};

#endif /* ANDROIDASSET_H_ */
