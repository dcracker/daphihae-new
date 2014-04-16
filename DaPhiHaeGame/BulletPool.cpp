#include "stdafx.h"
#include "BulletPool.h"

#include "Bullet.h"

BulletPool::BulletPool()
{
}


BulletPool::~BulletPool()
{
	while ( mBulletPool.empty() == false ) {
		delete mBulletPool.top();
		mBulletPool.pop();
	}
}

Bullet* BulletPool::NewBullet() {

	Bullet* newBullet = NULL;
	if ( mBulletPool.empty() ) {
		newBullet = new Bullet();
	}
	else {
		newBullet = mBulletPool.top();
		mBulletPool.pop();
	}
	return newBullet;
}

void BulletPool::PoolBullet( Bullet* bullet ) {
	mBulletPool.push( bullet );
}