#pragma once
#include "CollisionCircle.h"

class SpriteBatcher;

class Ship
{
public:
	enum MoveDirection {
		LEFT = -1,
		NEUTRAL = 0,
		RIGHT = 1,
	};

public:
	Ship( float initialPositionX, float initialPositionY );
	~Ship();

	void SetMoveDirection( MoveDirection direction );
	bool CheckCollision( const CollisionCircle& bullet ) const;
	void OnDead();

	void Update( float deltaTime );
	void Render( SpriteBatcher* batcher ) const;

private:
	static const float cMoveSpeed;
	static const float cWidthHalf;

private:
	float mCurrentSpeed;
	Vector2 mCurrentPosition;
	CollisionCircle mCollider;

	bool mAlive;
};

