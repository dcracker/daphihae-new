#pragma once

#include "../Interfaces/IFileIO.h"

class WindowsFileIO : public IFileIO
{
public:
	WindowsFileIO();
	~WindowsFileIO();

	IFileReader* ReadStorage( const char* fileName ) const;
	IFileWriter* WriteStorage( const char* fileName ) const;
	IFileReader* ReadAsset( const char* fileName ) const;

private:
	static bool DoesFolderExist( const char* folderName );

private:
	static const char* const cAssetPath;
	static const char* const cDataPath;
};

