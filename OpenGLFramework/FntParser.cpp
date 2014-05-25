#include "stdafx.h"
#include "FntParser.h"
#include "Interfaces/IFile.h"
#include "Interfaces/IPlatform.h"
#include "logger.h"

#define LOG_TAG "FntParser"
#define GET_BLOCK_SIZE( fntFile, type, sizeVarName )	\
	int sizeVarName;									\
	{													\
		BYTE id;										\
		ParseBlockHeader( fntFile, &id, &sizeVarName );	\
		assert( id == type::ID );						\
	}


FntParser::FntParser( const char* fntFileName )
	: mInfo( NULL )
	, mCommon( NULL )
	, mPages( NULL )
	, mChars( NULL )
	, mKernings( NULL )
{
	IFile* file = IPlatform::getInstancePtr()->GetFileIO()->ReadAsset( fntFileName );
	LOG_INFO( "%s\n", file->GetFileName() );
	ParseFile( file );
	delete file;
}


FntParser::~FntParser()
{
	delete mInfo->fontName;
	SAFE_DELETE( mInfo );
	SAFE_DELETE( mCommon );
	for ( int i=0; i < mPages->numPages; ++i ) {
		delete mPages->pageNames[i];
	}
	SAFE_DELETE( mPages );
	SAFE_DELETE( mChars );
	SAFE_DELETE( mKernings );
}

void FntParser::ParseFile( IFile* fntFile ) {
	ParseHeader( fntFile );
	mInfo = ParseInfo( fntFile );
	mCommon = ParseCommon( fntFile );
	mPages = ParsePages( fntFile, mCommon->pages );
	mChars = ParseChars( fntFile );
	mKernings = ParseKerning( fntFile );
}

void FntParser::ParseHeader( IFile* fntFile ) {
	char buf[4] = {0,};
	fntFile->ReadByte( buf, 3 );
	assert( strcmp( buf, "BMF" ) == 0 );

	BYTE versionNumber;
	fntFile->ReadByte( &versionNumber, 1 );
	assert( versionNumber == 3 );
}

void FntParser::ParseBlockHeader( IFile* fntFile, BYTE* out_blockId, int* out_blockSize ) {
	fntFile->ReadByte( out_blockId, 1 );
	fntFile->ReadByte( out_blockSize, 4 );
}

Info* FntParser::ParseInfo( IFile* fntFile ) {
	GET_BLOCK_SIZE( fntFile, Info, size );

	Info* info = new Info();
	unsigned int infoSize = sizeof(Info) - 4;	// except fontName pointer size
	fntFile->ReadByte( info, infoSize );

	unsigned int fontNameSize = size - infoSize;
	char* fontName = new char[fontNameSize];
	fntFile->ReadByte( fontName, fontNameSize );
	info->fontName = fontName;

	return info;
}

Common* FntParser::ParseCommon( IFile* fntFile ) {
	GET_BLOCK_SIZE( fntFile, Common, size );

	Common* common = new Common();
	fntFile->ReadByte( common, sizeof(Common) );
	return common;
}

Pages* FntParser::ParsePages( IFile* fntFile, int numPages ) {
	GET_BLOCK_SIZE( fntFile, Pages, size );

	Pages* pages = new Pages();
	pages->numPages = numPages;
	pages->pageNames = new const char*[numPages];

	// page name's length are all same.
	unsigned int sizeOfEachPageName = size / numPages;
	for ( int i=0; i < numPages; ++i ) {
		char* pageName = new char[sizeOfEachPageName];
		fntFile->ReadByte( pageName, sizeOfEachPageName );
		pages->pageNames[i] = pageName;
	}

	return pages;
}

Char** FntParser::ParseChars( IFile* fntFile ) {
	GET_BLOCK_SIZE( fntFile, Char, size );

	int numChars = size / sizeof(Char);	// TODO : save numChars
	Char** chars = new Char*[numChars];

	for ( int i=0; i < numChars; ++i ) {
		chars[i] = new Char();
		fntFile->ReadByte( chars[i], sizeof(Char) );
	}

	return chars;
}

KerningPairs** FntParser::ParseKerning( IFile* fntFile ) {
	GET_BLOCK_SIZE( fntFile, KerningPairs, size );

	int numKernings = size / sizeof(KerningPairs);
	KerningPairs** kernings = new KerningPairs*[numKernings];

	for ( int i=0; i < numKernings; ++i ) {
		kernings[i] = new KerningPairs();
		fntFile->ReadByte( kernings[i], sizeof(KerningPairs) );
	}

	return kernings;
}

GlyphDictionary FntParser::GetDictionary() const {
	GlyphDictionary dictionary;
	for ( int i=0; i < 95; ++i ) {
		Char* glyph = mChars[i];
		dictionary.insert( std::pair<char, Rect>( static_cast<char>( glyph->id ), GetGlyphRect( glyph ) ) );
	}

	return dictionary;
}

Rect FntParser::GetGlyphRect( Char* glyph ) {
	float x = static_cast<float>( glyph->x );
	float y = static_cast<float>( glyph->y );
	float width = static_cast<float>( glyph->width );
	float height = static_cast<float>( glyph->height );
	return Rect( x, x + width, y + height, y );
}