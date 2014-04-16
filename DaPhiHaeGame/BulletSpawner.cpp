#include "stdafx.h"
#include "BulletSpawner.h"

#include "GameScene.h"
#include "BulletPool.h"
#include "Bullet.h"
#include "Ship.h"
#include "Util.h"

BulletSpawner::BulletSpawner( float spawnInterval, Vector2 initialSpeed )
	: mRemainedTimeToSpawn( 0 )
	, mSpawnInterval( spawnInterval )
	, mInitialSpeed( initialSpeed )
{
	mBullets.clear();
}


BulletSpawner::~BulletSpawner()
{
	foreach ( Bullet*, it, mBullets ) {
		if ( *it != NULL ) {
			gBulletPool->PoolBullet( *it );
		}
	}
	mBullets.clear();
}

void BulletSpawner::Update( float deltaTime ) {
	UpdateExistBullets( deltaTime );
	SpawnNewBullets( deltaTime );
}

void BulletSpawner::UpdateExistBullets( float deltaTime ) {
	int lastIndex = mBullets.size() - 1;
	for ( int i = lastIndex; i >= 0; --i ) {
		Bullet* bullet = mBullets[i];

		bullet->Update( deltaTime );
		if ( bullet->GetTop() <= 0 ) {
			gBulletPool->PoolBullet( bullet );
			mBullets[i] = ( lastIndex == i ) ? NULL : mBullets[lastIndex];

			--lastIndex;
			mBullets.pop_back();
		}
	}
}

void BulletSpawner::SpawnNewBullets( float deltaTime ) {
	mRemainedTimeToSpawn -= deltaTime;
	if ( mRemainedTimeToSpawn <= 0 ) {
		mRemainedTimeToSpawn += mSpawnInterval;
		Bullet* bullet = gBulletPool->NewBullet();
		bullet->Init( Vector2( static_cast<float>(rand() % GameScene::cWorldWidth), GameScene::cWorldHeight + 5 ), mInitialSpeed );
		mBullets.push_back( bullet );
	}
}

void BulletSpawner::Render( SpriteBatcher* batcher ) const {
	foreach_const ( Bullet*, it, mBullets ) {
		(*it)->Render( batcher );
	}
}

bool BulletSpawner::CheckCollision( const Ship* ship ) const {
	foreach_const ( Bullet*, it, mBullets ) {
		if ( (*it)->CheckCollision( ship ) == true ) {
			return true;
		}
	}
	return false;
}

void BulletSpawner::Reset() {
	foreach ( Bullet*, it, mBullets ) {
		gBulletPool->PoolBullet( *it );
	}
	mBullets.clear();
}