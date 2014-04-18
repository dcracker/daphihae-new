#include "stdafx.h"
#include "SpriteAtlas.h"
#include "Texture.h"
#include "Util.h"

/*	TODO
	Register �Ŀ� index ���� �ٷ� ��ȯ���� �ʰ� �ڵ�� ��ȯ�ϵ��� ����.
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

unsigned int SpriteAtlas::RegisterAnimation( float frameDuration, Rect animArea, Vector2 frameSize ) {
	SpriteAnimation anim( frameDuration );

	int numHorizontal = static_cast<int>(animArea.GetWidth() / frameSize.x);
	int numVertical = static_cast<int>(animArea.GetHeight() / frameSize.y);

	Vector2 start( animArea.GetLeft(), animArea.GetBottom() );

	for ( int v=0; v < numVertical; ++v ) {
		for ( int h=0; h < numHorizontal; ++h ) {
			Rect frame( start.x + frameSize.x * h,
						start.x + frameSize.x * (h + 1),
						start.y + frameSize.y * v,
						start.y + frameSize.y * (v + 1) );
			anim.AddFrame( RegisterSprite( frame ) );
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
	return Rect (	originalCoord.GetLeft() / width,	originalCoord.GetRight() / width,
					originalCoord.GetBottom() / height,	originalCoord.GetTop() / height );
}

bool SpriteAtlas::TextureHasLoaded() {
	return GetWidth() > 0;
}