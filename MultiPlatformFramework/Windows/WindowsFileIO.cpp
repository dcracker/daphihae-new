#include "stdafx.h"
#include "WindowsFileIO.h"
#include "WindowsFile.h"
#include "WindowsFileReader.h"
#include "WindowsFileWriter.h"

const char* const WindowsFileIO::cAssetPath = "./Resources/";
const char* const WindowsFileIO::cDataPath = "./Data/";

#include "logger.h"
#define LOG_TAG "File"

WindowsFileIO::WindowsFileIO()
{
}


WindowsFileIO::~WindowsFileIO()
{
}

IFileReader* WindowsFileIO::ReadStorage( const char* fileName ) const {
	WindowsFile* openFile = new WindowsFile( cDataPath, fileName, GENERIC_READ );

	if ( openFile->IsVaild() ) {
		return new WindowsFileReader( openFile );
	}
	else {
		return NULL;
	}
}

IFileWriter* WindowsFileIO::WriteStorage( const char* fileName ) const {
	if ( DoesFolderExist( cDataPath ) == false ) {
		CreateDirectory( cDataPath, NULL );
	}

	return new WindowsFileWriter( cDataPath, fileName );
}

IFileReader* WindowsFileIO::ReadAsset( const char* fileName ) const {
	WindowsFile* openFile = new WindowsFile( cAssetPath, fileName, GENERIC_READ );

//	LOG_INFO( "read asset : %s ", fileName );
	if ( openFile->IsVaild() ) {
		return new WindowsFileReader( openFile );
	}
	else {
		LOG_ERROR( "cannot read asset : %s", fileName );
		assert( false && "cannot read asset" );
		return NULL;
	}
}

bool WindowsFileIO::DoesFolderExist( const char* folderName ) {
	DWORD attribute = GetFileAttributes( folderName );
	if ( attribute == INVALID_FILE_ATTRIBUTES ) {
		return false;
	}

	return (attribute & FILE_ATTRIBUTE_DIRECTORY) != 0;
}