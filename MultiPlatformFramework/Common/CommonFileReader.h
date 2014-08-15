#ifndef CommonFileReader_H_
#define CommonFileReader_H_


#include "Interfaces/IFileReader.h"

class CommonFile;

class CommonFileReader : public IFileReader
{
public:
	CommonFileReader( const char* fileName, FILE* file );
	~CommonFileReader();
	 
	const char* GetFileName() const;
	void Close();
	bool ReadByte( void* out_byteBuffer, int numByteToRead );

private:
	const char* mFileName;
	FILE* mFile;
};

#endif	// CommonFileReader_H_

