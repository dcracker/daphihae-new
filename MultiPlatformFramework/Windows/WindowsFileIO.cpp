#include "stdafx.h"
#include "WindowsFileIO.h"
#include "WindowsFile.h"

char* const WindowsFileIO::sAssetPath = "./Resources/";

WindowsFileIO::WindowsFileIO()
{
}


WindowsFileIO::~WindowsFileIO()
{
}

IFile* WindowsFileIO::ReadStorage( const char* fileName ) const {
	return NULL;
}

IFile* WindowsFileIO::WriteStorage( const char* fileName ) const {
	return NULL;
}

IFile* WindowsFileIO::ReadAsset( const char* fileName ) const {
	return new WindowsFile( sAssetPath, fileName, GENERIC_READ );
}