#ifndef IFileIO_H_
#define IFileIO_H_

#include "IFile.h"

class IFileIO {
public:
	virtual ~IFileIO () {}
	
	virtual IFile* ReadStorage( const char* fileName ) const = 0;
	virtual IFile* WriteStorage( const char* fileName ) const = 0;

	virtual IFile* ReadAsset( const char* fileName ) const = 0;
};

#endif	// IFileIO_H_
