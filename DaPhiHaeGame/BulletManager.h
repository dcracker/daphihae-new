#pragma once
#include <vector>

class Bullet;
class BulletPool;
class BulletSpawner;
class SpriteBatcher;
class Ship;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void Update( float deltaTime );
	void Render( SpriteBatcher* batcher ) const;

	void Reset();
	void AddBullet( const Vector2& initialPosition, const Vector2& initialVelocity );
	void AddSpawner( float spawnInterval, const Vector2& initialSpeed, float lifeTime );
	bool CheckCollision( const Ship* ship ) const;
	
private:
	void Clear();
	void UpdateBullets( float deltaTime );
	void UpdateSpawners( float deltaTime );

private:
	BulletPool*			mBulletPool;

	std::vector<Bullet*> mBullets;
	std::vector<BulletSpawner*> mSpawners;
};

