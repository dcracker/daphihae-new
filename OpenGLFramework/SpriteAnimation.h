#pragma once
#include <vector>
#include "Rect.h"

class SpriteAnimation
{
public:
	SpriteAnimation( float frameDuration );
	~SpriteAnimation();

	void AddFrame( unsigned int frame );

	unsigned int GetCurrentFrame( float frameTime ) const;

private:
	std::vector<unsigned int> mFrames;
	const float cFrameDuration;
};

