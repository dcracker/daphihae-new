#pragma once
#include <map>

typedef unsigned int SpriteHandle;
class SpriteBatcher;
class SpriteAtlas;
#include "FntParser.h"

class BitmapFont
{
public:
	BitmapFont( const char* fntFileName, SpriteAtlas* atlas, int left, int top );
	~BitmapFont();

	void RegisterGlyph( char character, SpriteHandle sprite );
	void DrawTexts( const char* string, Vector2 position, SpriteBatcher* batcher );

private:
	void CreateTable( GlyphDictionary* fntFile, SpriteAtlas* atlas, int left, int top );

private:
	const SpriteAtlas*				mAtlas;
	std::map<char, SpriteHandle>	mFontMap;
};

