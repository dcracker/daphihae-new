#pragma once
#include <vector>
#include <stack>

class SpriteBatcher;

class BulletSpawner
{
public:
	BulletSpawner( float spawnInterval, Vector2 initialSpeed, float lifeTime );
	~BulletSpawner();

	void Update( float deltaTime );
	void Render( SpriteBatcher* batcher ) const;
	bool IsAlive();

private:
	void SpawnNewBullets( float deltaTime );

private:
	float mSpawnInterval;
	Vector2 mInitialSpeed;

	float mRemainedTimeToSpawn;
	float mRemainedLifeTime;
};

