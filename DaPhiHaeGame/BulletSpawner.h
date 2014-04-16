#pragma once
#include <vector>
#include <stack>

class Ship;
class Bullet;
class SpriteBatcher;

class BulletSpawner
{
public:
	BulletSpawner( float spawnInterval, Vector2 initialSpeed );
	~BulletSpawner();

	void Update( float deltaTime );
	void Render( SpriteBatcher* batcher ) const;

	void Reset();
	bool CheckCollision( const Ship* ship ) const;

private:
	void UpdateExistBullets( float deltaTime );
	void SpawnNewBullets( float deltaTime );

private:
	std::vector<Bullet*> mBullets;
	
	float mSpawnInterval;
	Vector2 mInitialSpeed;

	float mRemainedTimeToSpawn;
};

