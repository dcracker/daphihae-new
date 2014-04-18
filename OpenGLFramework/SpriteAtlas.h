#ifndef SpriteAtlas_H_
#define SpriteAtlas_H_

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

	unsigned int RegisterAnimation( float frameDuration, Rect animArea, Vector2 frameSize );
	Rect GetAnimationFrame( unsigned int key, float frameTime ) const;

// override
	void Load( const IFileIO* fileIO );

private:
	static Rect AdjustCoordinate( Rect originalCoord, float width, float height );
	bool TextureHasLoaded();

private:
	std::vector<Rect> mSpriteCoords;
	std::vector<SpriteAnimation> mSpriteAnimation;
};


#endif	// SpriteAtlas_H_
