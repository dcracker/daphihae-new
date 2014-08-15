#include "stdafx.h"
#include "WindowsFileReader.h"
#include "WindowsFile.h"

WindowsFileReader::WindowsFileReader( const char* path, const char* fileName )
	: mReader( new WindowsFile( path, fileName, GENERIC_READ ) )
{
}

WindowsFileReader::WindowsFileReader( const WindowsFile* reader ) 
	: mReader ( reader )
{
}

WindowsFileReader::~WindowsFileReader()
{
	Close();
}

const char* WindowsFileReader::GetFileName() const {
	return mReader->GetFileName();
}

void WindowsFileReader::Close() {
	SAFE_DELETE( mReader );
}

bool WindowsFileReader::ReadByte( void* out_byteBuffer, int numByteToRead ) {
	return mReader->ReadByte( out_byteBuffer, numByteToRead );
}
