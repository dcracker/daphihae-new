#include "stdafx.h"
#include "SpriteAtlas.h"
#include "Texture.h"
#include "BitmapFont.h"
#include "Util.h"

/*	TODO
	Register 후에 index 값을 바로 반환하지 않고 핸들로 반환하도록 구현.
*/
SpriteAtlas::SpriteAtlas( const char* assetName )
	: Texture( assetName )
{
	mSpriteCoords.clear();
}

SpriteAtlas::~SpriteAtlas()
{
	mSpriteCoords.clear();
}

unsigned int SpriteAtlas::RegisterSprite( float left, float top, float right, float bottom ) {
	Rect pixelCoord( left, right, bottom, top );

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

unsigned int SpriteAtlas::RegisterAnimation( float frameDuration, float left, float top, float right, float bottom, Vector2 frameSize ) {
	Rect animArea( left, right, bottom, top );
	SpriteAnimation anim( frameDuration );

	int numHorizontal = static_cast<int>(animArea.GetWidth() / frameSize.x);
	int numVertical = static_cast<int>(-1 * animArea.GetHeight() / frameSize.y);
	assert( numHorizontal > 0 && numVertical > 0 );
	Vector2 start( animArea.GetLeft(), animArea.GetTop() );

	for ( int v=0; v < numVertical; ++v ) {
		for ( int h=0; h < numHorizontal; ++h ) {
			unsigned int sprite = RegisterSprite(	start.x + frameSize.x * h,
													start.y + frameSize.y * v,
													start.x + frameSize.x * (h + 1),
													start.y + frameSize.y * (v + 1) );
			anim.AddFrame( sprite );
		}
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
	return Rect (	originalCoord.GetLeft() / width,
					originalCoord.GetRight() / width,
					// reverse Y coordinates
					(height - originalCoord.GetBottom()) / height,
					(height - originalCoord.GetTop()) / height );
}

bool SpriteAtlas::TextureHasLoaded() {
	return GetWidth() > 0;
}