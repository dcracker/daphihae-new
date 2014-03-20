#ifndef TEXTURE_H_
#define TEXTURE_H_

class IFileIO;
class Image;
class Texture {
public:
	Texture( const IFileIO* io, const char* fileName );
	~Texture();

public:
	int GetWidth() const;
	int GetHeight() const;

	void Load();
	void Bind() const;
	static void Unbind();

	void SetFilter( GLint filterMode );
	void SetFilter( GLint minFilter, GLint magFilter );
	void SetWrapMode( GLint uv );
	void SetWrapMode( GLint u, GLint v );

private:
	static GLuint GenerateGLTexture( Image* image );
	static bool HasAlpha( GLint colorFormat );

private:
	const IFileIO* const 	cFileIO;
	const char* const 		cFileName;

	int		mWidth;
	int		mHeight;
	bool	mHasAlpha;
	GLuint	mTextureId;

	GLint	mMinFilter;
	GLint	mMagFilter;
	GLint	mWrapModeU;	// s
	GLint	mWrapModeV;	// t
};

#endif /* TEXTURE_H_ */
