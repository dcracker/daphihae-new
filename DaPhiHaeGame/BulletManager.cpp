#include "stdafx.h"
#include "BulletManager.h"

#include "Bullet.h"
#include "BulletPool.h"
#include "BulletSpawner.h"
#include "StageInformation.h"
#include "Util.h"

BulletManager::BulletManager()
	: mBulletPool( new BulletPool() )
	, mStageInfo( new StageInformation() )
{
}

BulletManager::~BulletManager()
{
	Util::FreePointerVector( mSpawners );
	Util::FreePointerVector( mBullets );
	SAFE_DELETE( mBulletPool );
	SAFE_DELETE( mStageInfo );
}

void BulletManager::Update( float deltaTime ) {
	UpdateBullets( deltaTime );
	UpdateSpawners( deltaTime );
}

void BulletManager::Render( SpriteBatcher* batcher ) const {
	foreach_const ( Bullet*, it, mBullets ) {
		(*it)->Render( batcher );
	}
}

void BulletManager::Reset() {
	Clear();
	Init();
}

void BulletManager::AddBullet( const Vector2& initialPosition, const Vector2& initialVelocity ) {
	Bullet* bullet = gBulletPool->NewBullet();
	bullet->Init( initialPosition, initialVelocity );
	mBullets.push_back( bullet );
}

void BulletManager::AddSpawner( float spawnInterval, const Vector2& initialSpeed, float lifeTime ) {
	mSpawners.push_back( new BulletSpawner( spawnInterval, initialSpeed, lifeTime ) );
}

bool BulletManager::CheckCollision( const Ship* ship ) const {
	foreach_const ( Bullet*, it, mBullets ) {
		if ( (*it)->CheckCollision( ship ) == true ) {
			return true;
		}
	}
	return false;
}

void BulletManager::Clear() {
	foreach ( Bullet*, it, mBullets ) {
		if ( *it != NULL ) {
			gBulletPool->PoolBullet( *it );
		}
	}
	mBullets.clear();

	Util::FreePointerVector( mSpawners );
}

void BulletManager::Init() {
	mStageInfo->Retry();
}

void BulletManager::UpdateBullets( float deltaTime ) {
	int lastIndex = mBullets.size() - 1;
	for ( int i = lastIndex; i >= 0; --i ) {
		Bullet* bullet = mBullets[i];

		bullet->Update( deltaTime );
		if ( bullet->IsAlive() == false ) {
			gBulletPool->PoolBullet( bullet );
			mBullets[i] = ( lastIndex == i ) ? NULL : mBullets[lastIndex];

			--lastIndex;
			mBullets.pop_back();
		}
	}
}

void BulletManager::UpdateSpawners( float deltaTime ) {
	int lastIndex = mSpawners.size() - 1;
	for ( int i = lastIndex; i >= 0; --i ) {
		BulletSpawner* spawner = mSpawners[i];

		spawner->Update( deltaTime );
		if ( spawner->IsAlive() == false ) {
			delete spawner;
			mSpawners[i] = ( lastIndex == i ) ? NULL : mSpawners[lastIndex];

			--lastIndex;
			mSpawners.pop_back();
		}
	}

	mStageInfo->Update( deltaTime );
}