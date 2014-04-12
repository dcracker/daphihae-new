#include "stdafx.h"
#include "SpriteAtlas.h"
#include "Texture.h"

SpriteAtlas::SpriteAtlas( const char* assetName )
	: Texture( assetName )
{
	mSpriteCoords.clear();
}

SpriteAtlas::~SpriteAtlas()
{
	mSpriteCoords.clear();
}

const Rect* SpriteAtlas::RegisterSprite( int key, Rect pixelCoord ) {
	if ( TextureHasLoaded() == false ) {
		mSpriteCoords[key] = pixelCoord;
	}
	else {
		mSpriteCoords[key] = AdjustCoordinate( pixelCoord, static_cast<float>(GetWidth()), static_cast<float>(GetHeight()) );
	}
	return &(mSpriteCoords[key]);
}

Rect SpriteAtlas::GetSpriteCoord( int key ) const {
	std::map<int, Rect>::const_iterator found = mSpriteCoords.find( key );
	assert( found != mSpriteCoords.end() );

	return found->second;
}
void SpriteAtlas::Load( const IFileIO* fileIO ) {
	bool notInitializedYet = !TextureHasLoaded();
	Texture::Load( fileIO );

	if ( notInitializedYet ) {
		float width = static_cast<float>(GetWidth());
		float height = static_cast<float>(GetHeight());
		for ( std::map<int, Rect>::iterator it = mSpriteCoords.begin(); it != mSpriteCoords.end(); ++it ) {
			it->second = AdjustCoordinate( it->second, width, height );
		}
	}
}

Rect SpriteAtlas::AdjustCoordinate( Rect originalCoord, float width, float height ) {
	return Rect (	originalCoord.GetLeft() / width,	originalCoord.GetRight() / width,
					originalCoord.GetBottom() / height,	originalCoord.GetTop() / height );
}

bool SpriteAtlas::TextureHasLoaded() {
	return GetWidth() > 0;
}