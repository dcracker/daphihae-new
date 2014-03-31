#include "stdafx.h"
#include "WindowsFile.h"

#include "logger.h"
#define LOG_TAG "File"

WindowsFile::WindowsFile( const char* path, const char* fileName, DWORD access )
	: cFileName( fileName )
	, mFileHandle( INVALID_HANDLE_VALUE )
{
	// path + fileName
	int filePathLength = strlen( path ) + strlen( fileName ) + 1;
	char* filePath = new char[filePathLength];
	strcpy_s( filePath, filePathLength, path );
	strcat_s( filePath, filePathLength, fileName );
	
	// open
	mFileHandle = CreateFile( filePath, access, 0, 0, GetCreationDisposition( access ), 0, 0 );
	if ( mFileHandle == INVALID_HANDLE_VALUE ) {
		LOG_ERROR( "cannot read asset : %s", filePath );
		assert( false && "cannot read asset" );
	}

	delete[] filePath;
}

WindowsFile::~WindowsFile()
{
	CloseHandle( mFileHandle );
}

const char* WindowsFile::GetFileName( ) {
	return cFileName;
}

bool WindowsFile::ReadByte( void* out_byteBuffer, int numByteToRead ) {
	DWORD byteToRead = static_cast<DWORD>(numByteToRead);
	DWORD byteHasRead = 0;
	ReadFile( mFileHandle, out_byteBuffer, byteToRead, &byteHasRead, NULL );
	return (byteHasRead == byteToRead);
}

DWORD WindowsFile::GetCreationDisposition( DWORD access ) {

	bool read =  ((access & GENERIC_READ)  != (DWORD)0);
	bool write = ((access & GENERIC_WRITE) != (DWORD)0);

	if ( read && write ) {
		return OPEN_ALWAYS;
	}
	else if ( read && !write ) {
		return OPEN_EXISTING;
	}
	else if ( !read && write ) {
		return CREATE_ALWAYS;
	}
	return 0;
}