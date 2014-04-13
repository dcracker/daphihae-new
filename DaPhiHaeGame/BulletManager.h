#pragma once
#include <vector>
#include <stack>

class Ship;
class Bullet;
class SpriteBatcher;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void Update( float deltaTime );
	void Render( SpriteBatcher* batcher ) const;

	bool CheckCollision( const Ship* ship ) const;

private:
	void UpdateExistBullets( float deltaTime );
	void SpawnNewBullets( float deltaTime );

private:
	static Bullet* NewBullet();
	static void PoolBullet( Bullet* bullet );
	
private:
	static float cSpawnInterval;
	static std::stack<Bullet*> sBulletPool;

private:
	std::vector<Bullet*> mBullets;

	float mRemainedTimeToSpawn;
};

