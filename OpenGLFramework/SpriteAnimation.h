#pragma once
#include <vector>

class Rect;

class SpriteAnimation
{
private:
	struct Keyframe {
		const Rect* const frame;
		const float duration;
	};
public:
	SpriteAnimation();
	SpriteAnimation( const SpriteAnimation& source );
	~SpriteAnimation();

	void AddFrame( const Rect* keyframe, float frameDuration );
	void Reset();

	void Update( float deltaTime );
	const Rect* GetCurrentFrame() const;

private:
	std::vector<Keyframe> mKeyFrames;
	float mCurrentTime;
	unsigned int mCurrentFrame;
};

