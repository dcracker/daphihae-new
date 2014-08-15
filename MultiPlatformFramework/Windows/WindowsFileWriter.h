#pragma once
#include "Interfaces/IFileWriter.h"

class WindowsFile;
class WindowsFileWriter : public IFileWriter
{
public:
	WindowsFileWriter( const char* path, const char* fileName );
	~WindowsFileWriter();
	
	const char* GetFileName() const;
	void Close();
	bool WriteByte( const void* byteBuffer, int numByteToWrite );

private:
	WindowsFile* mWriter;
};

