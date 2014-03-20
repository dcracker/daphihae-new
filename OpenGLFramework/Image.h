#ifndef IMAGE_H_
#define IMAGE_H_

class IFile;

class Image {
public:
	typedef unsigned char BYTE;

private:
	Image( int width, int height, GLint colorFormat, BYTE* byteBuffer );
public:
	~Image();

public:
	const int cWidth;
	const int cHeight;
	const GLint cColorFormat;
	const BYTE* const cImageData;

public:
	static Image* LoadPNG( IFile* file );
};

#endif /* IMAGE_H_ */
