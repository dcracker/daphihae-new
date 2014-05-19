#include "stdafx.h"
#include "BulletSpawner.h"

#include "GameScene.h"
#include "BulletManager.h"

BulletSpawner::BulletSpawner( BulletManager* manager, float spawnInterval, Vector2 initialSpeed, float lifeTime )
	: mRemainedTimeToSpawn( 0 )
	, mSpawnInterval( spawnInterval )
	, mInitialSpeed( initialSpeed )
	, mRemainedLifeTime( lifeTime )
	, mBulletManager( manager )
{
}


BulletSpawner::~BulletSpawner()
{
}

void BulletSpawner::Update( float deltaTime ) {
	mRemainedLifeTime -= deltaTime;
	SpawnNewBullets( deltaTime );
}

void BulletSpawner::SpawnNewBullets( float deltaTime ) {
	mRemainedTimeToSpawn -= deltaTime;
	if ( mRemainedTimeToSpawn <= 0 ) {
		mRemainedTimeToSpawn += mSpawnInterval;
		mBulletManager->AddBullet( Vector2( static_cast<float>(rand() % GameScene::cWorldWidth), GameScene::cWorldHeight + 5 ), mInitialSpeed );
	}
}

void BulletSpawner::Render( SpriteBatcher* batcher ) const {
	
}

bool BulletSpawner::IsAlive() {
	return mRemainedLifeTime > 0;
}