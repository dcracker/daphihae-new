#pragma once

class SpriteBatcher;

class CollisionCircle
{
public:
	CollisionCircle( const Vector2& parentPosition, float radius );
	~CollisionCircle();

	bool CheckCollision( const CollisionCircle& subject ) const;
	void Render( SpriteBatcher* batcher ) const;

private:
	const Vector2& mPosition;
	float mRadius;
};

