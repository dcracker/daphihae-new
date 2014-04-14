#include "stdafx.h"
#include "SpriteAnimation.h"


SpriteAnimation::SpriteAnimation( float frameDuration )
	: cFrameDuration( frameDuration )
{
	mFrames.clear();
}

SpriteAnimation::~SpriteAnimation()
{
	mFrames.clear();
}

void SpriteAnimation::AddFrame( unsigned int keyframe ) {
	mFrames.push_back( keyframe );
}

unsigned int SpriteAnimation::GetCurrentFrame( float frameTime ) const {
	unsigned int currentFrame = frameTime / cFrameDuration;
	if ( currentFrame >= mFrames.size() ) {
		currentFrame = mFrames.size() - 1;
	}
	return mFrames[currentFrame];
}