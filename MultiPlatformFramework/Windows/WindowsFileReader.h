#pragma once

#include "Interfaces/IFileReader.h"

class WindowsFile;

class WindowsFileReader : public IFileReader
{
public:
	WindowsFileReader( const char* path, const char* fileName );
	WindowsFileReader( const WindowsFile* reader );
	~WindowsFileReader();
	 
	const char* GetFileName() const;
	void Close();
	bool ReadByte( void* out_byteBuffer, int numByteToRead );

private:
	const WindowsFile* mReader;
};

