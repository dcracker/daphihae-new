#include "stdafx.h"
#include "CommonFileWriter.h"
#include <stdio.h>

CommonFileWriter::CommonFileWriter( const char* fileName, FILE* file )
	: mFile( file )
	, mFileName( fileName )
{
}


CommonFileWriter::~CommonFileWriter()
{
	Close();
}

const char* CommonFileWriter::GetFileName() const {
	return mFileName;
}

void CommonFileWriter::Close() {
	fclose( mFile );
}

bool CommonFileWriter::WriteByte( const void* byteBuffer, int numBytesToWrite ) {
	int bytesHasWritten = fwrite( byteBuffer, 1, numBytesToWrite, mFile );
	return (bytesHasWritten == numBytesToWrite);
}
