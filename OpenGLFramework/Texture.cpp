
#include "stdafx.h"

#include "Texture.h"
#include "Interfaces/IFileIO.h"
#include "Image.h"

Texture::Texture( const IFileIO* io, const char* fileName )
	: cFileName( fileName )
	, cFileIO( io )
	, mWidth( 0 )
	, mHeight( 0 )
	, mHasAlpha( false )
	, mTextureId( 0 )
	, mMinFilter( GL_NEAREST )
	, mMagFilter( GL_NEAREST )
	, mWrapModeU( GL_CLAMP_TO_EDGE )
	, mWrapModeV( GL_CLAMP_TO_EDGE )
{
}

Texture::~Texture() {
	mTextureId = 0;
}

void Texture::Load() {
	IFile* asset = cFileIO->ReadAsset( cFileName );
	Image* image = Image::LoadPNG( asset );

	mTextureId = GenerateGLTexture( image );
	mWidth = image->cWidth;
	mHeight = image->cHeight;
	mHasAlpha = HasAlpha( image->cColorFormat );

	delete image;
	delete asset;
}

bool Texture::HasAlpha( GLint colorFormat ) {
	return ( colorFormat == GL_RGBA ) || ( colorFormat == GL_LUMINANCE_ALPHA );
}

GLuint Texture::GenerateGLTexture( Image* image ) {

	GLuint id;
	glGenTextures( 1, &id );
	glBindTexture( GL_TEXTURE_2D, id );
	glTexImage2D( GL_TEXTURE_2D, 0, image->cColorFormat, image->cWidth, image->cHeight, 0, image->cColorFormat, GL_UNSIGNED_BYTE, image->cImageData );

	return id;
}

void Texture::Bind() const {
	glBindTexture( GL_TEXTURE_2D, mTextureId );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinFilter );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagFilter );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapModeU );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapModeV );

	if ( mHasAlpha == true ) {
		glEnable( GL_BLEND );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void Texture::Unbind() {
	glBindTexture( GL_TEXTURE_2D, 0 );
	glDisable( GL_BLEND );
}

void Texture::SetFilter( GLint filterMode ) {
	SetFilter( filterMode, filterMode );
}

void Texture::SetFilter( GLint minFilter, GLint magFilter ) {
	mMinFilter = minFilter;
	mMagFilter = magFilter;
}

void Texture::SetWrapMode( GLint uv ) {
	SetWrapMode( uv, uv );
}

void Texture::SetWrapMode( GLint u, GLint v ) {
	mWrapModeU = u;
	mWrapModeV = v;
}

int Texture::GetWidth() const {
	return mWidth;
}

int Texture::GetHeight() const {
	return mHeight;
}