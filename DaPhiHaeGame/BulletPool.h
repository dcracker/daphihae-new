#pragma once
#include "TSingleton.hpp"
#include <stack>

class Bullet;

#define gBulletPool BulletPool::getInstancePtr()

class BulletPool : public TSingleton<BulletPool>
{
public:
	BulletPool();
	~BulletPool();

	Bullet* NewBullet();
	void PoolBullet( Bullet* bullet );

private:
	std::stack<Bullet*> mBulletPool;
};

