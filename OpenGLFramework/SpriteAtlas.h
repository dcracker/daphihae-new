#pragma once
#include <map>
#include "Rect.h"
#include "Texture.h"

class IFileIO;

class SpriteAtlas : public Texture
{
public:
	SpriteAtlas( const char* assetName );
	~SpriteAtlas();

	const Rect* RegisterSprite( int key, Rect pixelCoord );
	const Rect* GetSpriteCoord( int key ) const;

// override
	void Load( const IFileIO* fileIO );

private:
	static Rect AdjustCoordinate( Rect originalCoord, float width, float height );
	bool TextureHasLoaded();

private:
	std::map<int, Rect> mSpriteCoords;
};

