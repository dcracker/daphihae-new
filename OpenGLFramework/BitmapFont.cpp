#include "stdafx.h"
#include "BitmapFont.h"
#include "SpriteAtlas.h"
#include "SpriteBatcher.h"
#include "Rect.h"
#include "FntParser.h"

BitmapFont::BitmapFont( const char* fntFileName, SpriteAtlas* atlas, int left, int top )
	: mAtlas( atlas )
{
	FntParser parser( fntFileName );
	mFontMap.clear();
	GlyphDictionary dictionary = parser.GetDictionary();
	CreateTable( &dictionary, atlas, left, top );
}


BitmapFont::~BitmapFont()
{
	mAtlas = NULL;
	mFontMap.clear();
}

void BitmapFont::CreateTable( GlyphDictionary* dictionary, SpriteAtlas* atlas, int left, int top ) {
	GlyphDictionary::iterator it;
	for ( it = dictionary->begin(); it != dictionary->end(); ++it ) {
		const Rect& glyphRect = it->second;
		SpriteHandle handle = atlas->RegisterSprite( left + glyphRect.GetLeft(), top + glyphRect.GetTop(), left + glyphRect.GetRight(), top + glyphRect.GetBottom() );
		RegisterGlyph( it->first, handle );
	}
}

void BitmapFont::RegisterGlyph( char character, SpriteHandle sprite ) {
	mFontMap[character] = sprite;
}

void BitmapFont::DrawTexts( const char* string, Vector2 startPosition, SpriteBatcher* batcher ) {
	int length = strlen( string );
	for ( int i=0; i < length; ++i ) {
		char character = string[i];
		std::map<char, SpriteHandle>::iterator found = mFontMap.find( character );
		if ( found == mFontMap.end() ) {
			continue;
		}
		Rect size = mAtlas->GetSpriteCoord( found->second );
		float glyphWidth = size.GetWidth() * mAtlas->GetWidth();
		float glyphHeight = size.GetHeight() * mAtlas->GetHeight();
		Rect position( startPosition.x, startPosition.x + glyphWidth, startPosition.y, startPosition.y + glyphHeight );
		batcher->DrawSprite( position, found->second );
		startPosition.x += glyphWidth;
	}
}
