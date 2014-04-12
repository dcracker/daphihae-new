#include "stdafx.h"
#include "BulletManager.h"

#include "GameScene.h"
#include "Bullet.h"
#include "Util.h"

float BulletManager::cSpawnInterval = 0.1f;
std::stack<Bullet*> BulletManager::sBulletPool;

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
	UpdateExistBullets( deltaTime );
	SpawnNewBullets( deltaTime );
}

void BulletManager::UpdateExistBullets( float deltaTime ) {
	int lastIndex = mBullets.size() - 1;
	for ( int i = lastIndex; i >= 0; --i ) {
		Bullet* bullet = mBullets[i];

		bullet->Update( deltaTime );
		if ( bullet->GetTop() <= 0 ) {
			PoolBullet( bullet );
			mBullets[i] = ( lastIndex == i ) ? NULL : mBullets[lastIndex];

			--lastIndex;
			mBullets.pop_back();
		}
	}
}

void BulletManager::SpawnNewBullets( float deltaTime ) {
	mRemainedTimeToSpawn -= deltaTime;
	if ( mRemainedTimeToSpawn <= 0 ) {
		mRemainedTimeToSpawn += cSpawnInterval;
		Bullet* bullet = NewBullet();
		bullet->Init( Vector2( static_cast<float>(rand() % GameScene::cWorldWidth), GameScene::cWorldHeight + 5 ), Vector2( 0, -300 ) );
		mBullets.push_back( bullet );
	}
}

void BulletManager::Render( SpriteBatcher* batcher ) const {
	foreach_const ( Bullet*, it, mBullets ) {
		(*it)->Render( batcher );
	}
}


Bullet* BulletManager::NewBullet() {

	Bullet* newBullet = NULL;
	if ( sBulletPool.empty() ) {
		newBullet = new Bullet();
	}
	else {
		newBullet = sBulletPool.top();
		sBulletPool.pop();
	}
	return newBullet;
}

void BulletManager::PoolBullet( Bullet* bullet ) {
	sBulletPool.push( bullet );
}