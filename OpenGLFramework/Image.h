#ifndef IMAGE_H_
#define IMAGE_H_

#include "Common/CommonHeaders.h"

class IFileReader;

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
	static Image* LoadPNG( IFileReader* file );
};

#endif /* IMAGE_H_ */
