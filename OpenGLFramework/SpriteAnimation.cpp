#include "stdafx.h"
#include "SpriteAnimation.h"


SpriteAnimation::SpriteAnimation()
	: mCurrentTime( 0 )
	, mCurrentFrame( 0 )
{
	mKeyFrames.clear();
}

SpriteAnimation::SpriteAnimation( const SpriteAnimation& source )
	: mKeyFrames( source.mKeyFrames )
{
}

SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::AddFrame( const Rect* keyframe, float frameDuration ) {
	mKeyFrames.push_back( { keyframe, frameDuration } );
}

void SpriteAnimation::Reset() {
	mCurrentTime = 0;
	mCurrentFrame = 0;
}

void SpriteAnimation::Update( float deltaTime ) {
	if ( mCurrentFrame >= mKeyFrames.size() - 1 ) {
		return;
	}

	mCurrentTime += deltaTime;
	while ( mCurrentFrame < mKeyFrames.size() - 1
		&& mCurrentTime >= mKeyFrames[mCurrentFrame].duration )
	{
		mCurrentTime -= mKeyFrames[mCurrentFrame].duration;
		++mCurrentFrame;
	}
}

const Rect* SpriteAnimation::GetCurrentFrame() const {
	assert( mCurrentFrame < mKeyFrames.size() );
	return mKeyFrames[mCurrentFrame].frame;
}