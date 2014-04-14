#pragma once
#include <vector>
#include "Texture.h"
#include "Rect.h"
#include "SpriteAnimation.h"

class IFileIO;

class SpriteAtlas : public Texture
{
public:
	SpriteAtlas( const char* assetName );
	~SpriteAtlas();

	unsigned int RegisterSprite( Rect pixelCoord );
	Rect GetSpriteCoord( unsigned int ) const;

	unsigned int RegisterAnimation( float frameDuration, unsigned int numFrames, unsigned int frames[] );
	Rect GetAnimationFrame( unsigned int key, float frameTime ) const;

// override
	void Load( const IFileIO* fileIO );

private:
	static Rect AdjustCoordinate( Rect originalCoord, float width, float height );
	bool TextureHasLoaded();

private:
	std::vector<const Rect> mSpriteCoords;
	std::vector<const SpriteAnimation> mSpriteAnimation;
};

