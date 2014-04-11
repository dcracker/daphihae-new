#include "stdafx.h"
#include "BulletManager.h"

#include "Bullet.h"
#include "Util.h"

float BulletManager::cSpawnInterval = 1;

BulletManager::BulletManager()
	: mRemainedTimeToSpawn( 0 )
{
	mBullets.clear();
}


BulletManager::~BulletManager()
{
	foreach ( Bullet*, it, mBullets ) {
		if ( *it != NULL ) {
			delete (*it);
		}
	}
	mBullets.clear();
}

void BulletManager::Update( float deltaTime ) {
	SpawnNewBullets( deltaTime );
	UpdateExistBullets( deltaTime );
}

void BulletManager::UpdateExistBullets( float deltaTime ) {
	foreach ( Bullet*, it, mBullets ) {
		(*it)->Update( deltaTime );
	}
}

void BulletManager::SpawnNewBullets( float deltaTime ) {
	mRemainedTimeToSpawn -= deltaTime;
	if ( mRemainedTimeToSpawn <= 0 ) {
		mRemainedTimeToSpawn += cSpawnInterval;
		mBullets.push_back( new Bullet( Vector2( 0, -10 ), Vector2( 0, -300 ) ) );
	}
}

void BulletManager::Render( SpriteBatcher* batcher ) const {
	foreach_const ( Bullet*, it, mBullets ) {
		(*it)->Render( batcher );
	}
}