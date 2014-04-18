#include "stdafx.h"
#include "Bullet.h"

#include "Ship.h"
#include "SpriteBatcher.h"
#include "Asset.h"

float Bullet::cSizeHalf = 5.f;

Bullet::Bullet()
	: mPosition( 0, 0 )
	, mVelocity( 0, 0 )
	, mCollider( mPosition, cSizeHalf )
{
}

Bullet::~Bullet()
{
}

void Bullet::Update( float deltaTime ) {
	mPosition += mVelocity * deltaTime;
}

void Bullet::Render( SpriteBatcher* batcher ) const {
//	mCollider.Render( batcher );
	batcher->DrawSprite( Rect( mPosition, Vector2( cSizeHalf * 2, cSizeHalf * 2 ) ), gAsset->oldBullet );
}

void Bullet::Init( const Vector2& initialPosition, const Vector2& initialVelocity ) {
	mPosition = initialPosition;
	mVelocity = initialVelocity;
}

bool Bullet::CheckCollision( const Ship* ship ) const {
	return ship->CheckCollision( mCollider );
}

bool Bullet::IsAlive() const {
	return GetTop() > 0;
}

float Bullet::GetLeft() const {
	return mPosition.x - cSizeHalf;
}

float Bullet::GetRight() const {
	return mPosition.x + cSizeHalf;
}

float Bullet::GetTop() const {
	return mPosition.y + cSizeHalf;
}

float Bullet::GetBottom() const {
	return mPosition.y - cSizeHalf;
}