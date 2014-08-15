#ifndef IFILE_H_
#define IFILE_H_

class IFile {
public:
	virtual ~IFile() {}

	virtual const char* GetFileName() const = 0;
	virtual void Close() = 0;
};

#endif /* IFILE_H_ */
