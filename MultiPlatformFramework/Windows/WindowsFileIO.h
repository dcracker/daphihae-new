#pragma once

#include "../Interfaces/IFileIO.h"

class WindowsFileIO : public IFileIO
{
public:
	WindowsFileIO();
	~WindowsFileIO();

	IFile* ReadStorage( const char* fileName ) const;
	IFile* WriteStorage( const char* fileName ) const;
	IFile* ReadAsset( const char* fileName ) const;

private:
	static char* const sAssetPath;
};

