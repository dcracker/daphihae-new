#include "stdafx.h"
#include "CommonFileReader.h"
#include <stdio.h>

CommonFileReader::CommonFileReader( const char* fileName, FILE* file )
	: mFile( file )
	, mFileName( fileName )
{
}

CommonFileReader::~CommonFileReader()
{
	Close();
}

const char* CommonFileReader::GetFileName() const {
	return mFileName;
}

void CommonFileReader::Close() {
	fclose( mFile );
	mFile = NULL;
}

bool CommonFileReader::ReadByte( void* out_byteBuffer, int numBytesToRead ) {
	int bytesHasRead = fread( out_byteBuffer, 1, numBytesToRead, mFile );
	return (bytesHasRead == numBytesToRead);
}
