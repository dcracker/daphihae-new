#include "stdafx.h"
#include "CommonFileIO.h"
#include "CommonFileReader.h"
#include "CommonFileWriter.h"

#include "logger.h"
#define LOG_TAG "File"

const char* const CommonFileIO::cReadMode = "rb";
const char* const CommonFileIO::cWriteMode = "wb";

CommonFileIO::CommonFileIO( const char* const assetPath, const char* const dataPath, const char* const extenalStoragePath )
	: mAssetPath( assetPath )
	, mDataPath( dataPath )
	, mExternalStoragePath( extenalStoragePath )
{
}


CommonFileIO::~CommonFileIO()
{
}

IFileReader* CommonFileIO::ReadData( const char* fileName ) const {
	return OpenFile<CommonFileReader>( mDataPath, fileName, cReadMode );
}

IFileWriter* CommonFileIO::WriteData( const char* fileName ) const {
	return OpenFile<CommonFileWriter>( mDataPath, fileName, cWriteMode );
}

IFileReader* CommonFileIO::ReadExternalStorage( const char* fileName ) const {
	return OpenFile<CommonFileReader>( mExternalStoragePath, fileName, cReadMode );
}

IFileWriter* CommonFileIO::WriteExternalStorage( const char* fileName ) const {
	return OpenFile<CommonFileWriter>( mExternalStoragePath, fileName, cWriteMode );
}

IFileReader* CommonFileIO::ReadAsset( const char* fileName ) const {
	return OpenFile<CommonFileReader>( mAssetPath, fileName, cReadMode );
}

template <typename T>
T* CommonFileIO::OpenFile( const char* path, const char* fileName, const char* mode ) {
	const char* fullPath = ConcatenateAsFullPath( path, fileName );
	FILE* openFile = fopen( fullPath, mode );
	delete fullPath;

	if ( openFile == NULL ) {
		return NULL;
	}
	else {
		return new T(fileName, openFile);
	}
}

const char* CommonFileIO::ConcatenateAsFullPath( const char* path, const char* fileName ) {
	int pathLength = strlen( path );
	int fullPathLength = pathLength + strlen( fileName ) + 2;
	char* fullPath = new char[fullPathLength];

	strcpy( fullPath, path );

	if ( path[pathLength - 1] != '/' ) {
		strcat( fullPath, "/" );
	}

	strcat( fullPath, fileName );
	return fullPath;
}
