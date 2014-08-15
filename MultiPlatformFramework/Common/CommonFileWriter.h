#ifndef CommonFileWriter_H_
#define CommonFileWriter_H_

#include "Interfaces/IFileWriter.h"

class CommonFileWriter : public IFileWriter
{
public:
	CommonFileWriter( const char* fileName, FILE* file );
	~CommonFileWriter();
	
	const char* GetFileName() const;
	void Close();
	bool WriteByte( const void* byteBuffer, int numByteToWrite );

private:
	const char* mFileName;
	FILE* mFile;
};


#endif	// CommonFileWriter_H_
