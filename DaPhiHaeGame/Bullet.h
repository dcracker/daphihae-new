#pragma once

class SpriteBatcher;

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Update( float deltaTime );
	void Render( SpriteBatcher* batcher ) const;

	void Init( const Vector2& initialPosition, const Vector2& initialVelocity );
	
	float GetLeft() const;
	float GetRight() const;
	float GetTop() const;
	float GetBottom() const;

private:
	static float cSizeHalf;

private:
	Vector2 mPosition;
	Vector2 mVelocity;
};

