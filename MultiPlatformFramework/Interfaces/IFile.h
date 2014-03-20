#ifndef IFILE_H_
#define IFILE_H_

class IFile {
public:
	virtual ~IFile() {}

	virtual const char* GetFileName() = 0;

	// open at create, close at destroy

	virtual bool ReadByte( void* out_byteBuffer, int numByteToRead ) = 0;
};

#endif /* IFILE_H_ */
