#include "stdafx.h"
#include "BitmapFont.h"
#include "SpriteAtlas.h"
#include "SpriteBatcher.h"

BitmapFont::BitmapFont( SpriteAtlas* atlas )
	: mAtlas( atlas )
{
	mFontMap.clear();
}


BitmapFont::~BitmapFont()
{
	mAtlas = NULL;
	mFontMap.clear();
}

void BitmapFont::RegisterGlyph( char character, SpriteHandle sprite ) {
	mFontMap[character] = sprite;
}

void BitmapFont::DrawTexts( const char* string, float x, float y, SpriteBatcher* batcher ) {
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
		Rect position( Vector2( x, y ), Vector2( glyphWidth, glyphHeight ) );
		batcher->DrawSprite( position, found->second );
		x += glyphWidth;
	}
}