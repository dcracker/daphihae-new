#include "stdafx.h"
#include "WindowsFileIO.h"

const char* const WindowsFileIO::cAssetPath = "./Resources/";
const char* const WindowsFileIO::cDataPath = "./Data/";

#include "logger.h"
#define LOG_TAG "File"

WindowsFileIO::WindowsFileIO()
	: CommonFileIO( cAssetPath, cDataPath, NULL )
{
}


WindowsFileIO::~WindowsFileIO()
{
}

IFileWriter* WindowsFileIO::WriteData( const char* fileName ) const {
	if ( DoesFolderExist( cDataPath ) == false ) {
		CreateDirectory( cDataPath, NULL );
	}

	return CommonFileIO::WriteData( fileName );
}

bool WindowsFileIO::DoesFolderExist( const char* folderName ) {
	DWORD attribute = GetFileAttributes( folderName );
	if ( attribute == INVALID_FILE_ATTRIBUTES ) {
		return false;
	}

	return (attribute & FILE_ATTRIBUTE_DIRECTORY) != 0;
}