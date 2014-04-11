#pragma once
#include <vector>

class Bullet;
class SpriteBatcher;

class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	void Update( float deltaTime );
	void Render( SpriteBatcher* batcher ) const;

private:
	void UpdateExistBullets( float deltaTime );
	void SpawnNewBullets( float deltaTime );
	
private:
	static float cSpawnInterval;

private:
	std::vector<Bullet*> mBullets;

	float mRemainedTimeToSpawn;
};

