#include "stdafx.h"
#include "SpriteAtlas.h"
#include "Texture.h"
#include "Util.h"

SpriteAtlas::SpriteAtlas( const char* assetName )
	: Texture( assetName )
{
	mSpriteCoords.clear();
}

SpriteAtlas::~SpriteAtlas()
{
	mSpriteCoords.clear();
}

unsigned int SpriteAtlas::RegisterSprite( Rect pixelCoord ) {
	if ( TextureHasLoaded() == false ) {
		mSpriteCoords.push_back( pixelCoord );
	}
	else {
		mSpriteCoords.push_back( AdjustCoordinate( pixelCoord, static_cast<float>(GetWidth()), static_cast<float>(GetHeight()) ) );
	}
	return mSpriteCoords.size() - 1;
}

Rect SpriteAtlas::GetSpriteCoord( unsigned int key ) const {
	assert( key >= 0 && key < mSpriteCoords.size() );
	return mSpriteCoords[key];
}

unsigned int SpriteAtlas::RegisterAnimation( float frameDuration, unsigned int numFrames, unsigned int frames[] ) {
	SpriteAnimation anim( frameDuration );

	for ( unsigned int i=0; i < numFrames; ++i ) {
		anim.AddFrame( frames[i] );
	}
	mSpriteAnimation.push_back( anim );
	return mSpriteAnimation.size() - 1;
}

Rect SpriteAtlas::GetAnimationFrame( unsigned int key, float frameTime ) const {
	assert( key >= 0 && key < mSpriteAnimation.size() );
	return mSpriteCoords[mSpriteAnimation[key].GetCurrentFrame( frameTime )];
}

void SpriteAtlas::Load( const IFileIO* fileIO ) {
	bool notInitializedYet = !TextureHasLoaded();
	Texture::Load( fileIO );

	if ( notInitializedYet ) {
		float width = static_cast<float>(GetWidth());
		float height = static_cast<float>(GetHeight());
		foreach ( Rect, it, mSpriteCoords ) {
			(*it) = AdjustCoordinate( *it, width, height );
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