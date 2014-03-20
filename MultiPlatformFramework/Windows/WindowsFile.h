#pragma once

#include "../Interfaces/IFile.h"

class WindowsFile : public IFile
{
public:
	WindowsFile( const char* path, const char* fileName, DWORD access );
	~WindowsFile();
	
	const char* GetFileName();
	bool ReadByte( void* out_byteBuffer, int numByteToRead );

private:
	DWORD GetCreationDisposition( DWORD access );

private:
	const char*	cFileName;
	HANDLE		mFileHandle;
};

