#pragma once

class WindowsFile
{
public:
	WindowsFile( const char* path, const char* fileName, DWORD access );
	~WindowsFile();
	
	const char* GetFileName() const;
	bool IsVaild() const;
	bool ReadByte( void* out_byteBuffer, int numByteToRead ) const;
	bool WriteByte( const void* byteBuffer, int numByteToWrite );

private:
	DWORD GetCreationDisposition( DWORD access );

private:
	const char*	cFileName;
	HANDLE		mFileHandle;
};

