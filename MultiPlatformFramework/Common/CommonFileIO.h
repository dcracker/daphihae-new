#pragma once

#include "../Interfaces/IFileIO.h"

class CommonFileReader;
class CommonFileWriter;

class CommonFileIO : public IFileIO
{
public:
	CommonFileIO( const char* const assetPath, const char* const dataPath, const char* const extenalStoragePath );
	virtual ~CommonFileIO();

	virtual IFileReader* ReadData( const char* fileName ) const;
	virtual IFileWriter* WriteData( const char* fileName ) const;

	virtual IFileReader* ReadExternalStorage( const char* fileName ) const;
	virtual IFileWriter* WriteExternalStorage( const char* fileName ) const;

	virtual IFileReader* ReadAsset( const char* fileName ) const;

private:
	static const char* ConcatenateAsFullPath( const char* path, const char* fileName );

	template <typename T>
	static T* OpenFile( const char* path, const char* fileName, const char* mode );

private:
	const char* const mAssetPath;
	const char* const mDataPath;
	const char* const mExternalStoragePath;

	static const char* const cReadMode;
	static const char* const cWriteMode;
};

