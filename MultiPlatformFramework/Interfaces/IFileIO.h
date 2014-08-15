#ifndef IFileIO_H_
#define IFileIO_H_

class IFileReader;
class IFileWriter;

class IFileIO {
public:
	virtual ~IFileIO () {}
	
	virtual IFileReader* ReadData( const char* fileName ) const = 0;
	virtual IFileWriter* WriteData( const char* fileName ) const = 0;

	virtual IFileReader* ReadExternalStorage( const char* fileName ) const = 0;
	virtual IFileWriter* WriteExternalStorage( const char* fileName ) const = 0;

	virtual IFileReader* ReadAsset( const char* fileName ) const = 0;
};

#endif	// IFileIO_H_
