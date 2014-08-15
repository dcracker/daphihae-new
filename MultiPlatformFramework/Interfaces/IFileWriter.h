#ifndef IFILE_WRITER_H_
#define IFILE_WRITER_H_

#include "IFile.h"

class IFileWriter : public IFile {
public:
	virtual ~IFileWriter() {}
	virtual bool WriteByte( const void* byteBuffer, int numByteToRead ) = 0;
};

#endif IFILE_WRITER_H_