#ifndef IFileIO_H_
#define IFileIO_H_

class IFileReader;
class IFileWriter;

class IFileIO {
public:
	virtual ~IFileIO () {}
	
	virtual IFileReader* ReadStorage( const char* fileName ) const = 0;
	virtual IFileWriter* WriteStorage( const char* fileName ) const = 0;

	virtual IFileReader* ReadAsset( const char* fileName ) const = 0;
};

#endif	// IFileIO_H_
