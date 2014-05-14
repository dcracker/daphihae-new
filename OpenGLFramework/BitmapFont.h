#pragma once
#include <map>

typedef unsigned int SpriteHandle;
class SpriteBatcher;
class SpriteAtlas;

class BitmapFont
{
public:
	BitmapFont( SpriteAtlas* atlas );
	~BitmapFont();

	void RegisterGlyph( char character, SpriteHandle sprite );
	void DrawTexts( const char* string, Vector2 position, SpriteBatcher* batcher );

private:
	SpriteAtlas*					mAtlas;
	std::map<char, SpriteHandle>	mFontMap;
};

