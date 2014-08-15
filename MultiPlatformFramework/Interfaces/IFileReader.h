#ifndef IFILE_READER_H_
#define IFILE_READER_H_

#include "IFile.h"

class IFileReader : public IFile {
public:
	virtual ~IFileReader() {}
	virtual bool ReadByte( void* out_byteBuffer, int numByteToRead ) = 0;
};

#endif // IFILE_READER_H_
