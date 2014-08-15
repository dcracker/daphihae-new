// ref : http://www.angelcode.com/products/bmfont/doc/file_format.html#bin
#pragma once
#include <map>
#include "Rect.h"

class IFileReader;

#pragma pack( push, 1 )
struct Info {
	static const BYTE ID = 1;

	short	fontSize;
	BYTE	bitField;
	BYTE	charSet;
	short	stretchH;
	BYTE	aa;
	BYTE	paddingUp;
	BYTE	paddingRight;
	BYTE	paddingDown;
	BYTE	paddingLeft;
	BYTE	spacingHoriz;
	BYTE	spacingVert;
	BYTE	outline;
	const char*	fontName;
};

struct Common {
	static const BYTE ID = 2;

	unsigned short	lineHeight;
	unsigned short	base;
	unsigned short	scaleW;
	unsigned short	scaleH;
	unsigned short	pages;
	BYTE			bitField;
	BYTE			alphaChnl;
	BYTE			redChnl;
	BYTE			geernChnl;
	BYTE			blueChnl;
};

struct Pages {
	static const BYTE ID = 3;

	int numPages;
	const char**	pageNames;
};

struct Char {
	static const BYTE ID = 4;

	unsigned int	id;
	unsigned short	x;
	unsigned short	y;
	unsigned short	width;
	unsigned short	height;
	short			xOffset;
	short			yOffset;
	short			xAdvance;
	BYTE			page;
	BYTE			chnl;
};

struct KerningPairs {
	static const BYTE ID = 5;

	unsigned int first;
	unsigned int second;
	short amount;
};
#pragma pack( pop )

typedef std::map<char, Rect> GlyphDictionary;
class FntParser
{
public:
	FntParser( const char* fntFileName );
	~FntParser();

	GlyphDictionary GetDictionary() const;

private:
	void ParseFile( IFileReader* fntFile );

private:
	static void ParseHeader( IFileReader* fntFile );
	static void ParseBlockHeader( IFileReader* fntFile, BYTE* out_blockId, int* out_blockSize );
	static Info* ParseInfo( IFileReader* fntFile );
	static Common* ParseCommon( IFileReader* fntFile );
	static Pages* ParsePages( IFileReader* fntFile, int numPages );
	static Char** ParseChars( IFileReader* fntFile );
	static KerningPairs** ParseKerning( IFileReader* fntFile );
	static Rect GetGlyphRect( Char* glyph );

private:
	Info*	mInfo;
	Common* mCommon;
	Pages*	mPages;
	Char**	mChars;
	KerningPairs**	mKernings;
};

