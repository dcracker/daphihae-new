#include "stdafx.h"
#include "WindowsFileWriter.h"
#include "WindowsFile.h"

WindowsFileWriter::WindowsFileWriter( const char* path, const char* fileName )
	: mWriter( new WindowsFile( path, fileName, GENERIC_WRITE ) )
{
}


WindowsFileWriter::~WindowsFileWriter()
{
	Close();
}

const char* WindowsFileWriter::GetFileName() const {
	return mWriter->GetFileName();
}

void WindowsFileWriter::Close() {
	SAFE_DELETE( mWriter );
}

bool WindowsFileWriter::WriteByte( const void* byteBuffer, int numByteToWrite ) {
	return mWriter->WriteByte( byteBuffer, numByteToWrite );
}
