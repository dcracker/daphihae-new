#pragma once

#include "../Common/CommonFileIO.h"

class WindowsFileIO : public CommonFileIO
{
public:
	WindowsFileIO();
	~WindowsFileIO();

	IFileWriter* WriteData( const char* fileName ) const;

private:
	static bool DoesFolderExist( const char* folderName );

private:
	static const char* const cAssetPath;
	static const char* const cDataPath;
};

