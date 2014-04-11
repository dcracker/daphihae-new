#pragma once

class Sprite;
class SpriteBatcher;

class Bullet
{
public:
	Bullet( Vector2 initialPosition, Vector2 initialVelocity );
	~Bullet();

	void Update( float deltaTime );
	void Render( SpriteBatcher* batcher ) const;

private:
	static float cSizeHalf;

private:
	Vector2 mPosition;
	Vector2 mVelocity;

	Sprite* mSprite;
};

