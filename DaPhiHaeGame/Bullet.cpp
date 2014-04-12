#include "stdafx.h"
#include "Bullet.h"

#include "SpriteBatcher.h"
#include "Asset.h"

float Bullet::cSizeHalf = 5.f;

Bullet::Bullet()
	: mPosition( 0, 0 )
	, mVelocity( 0, 0 )
{
}

Bullet::~Bullet()
{
}

void Bullet::Update( float deltaTime ) {
	mPosition += mVelocity * deltaTime;
}

void Bullet::Render( SpriteBatcher* batcher ) const {
	batcher->DrawSprite( Rect( mPosition, Vector2( cSizeHalf * 2, cSizeHalf * 2 ) ), *(gAsset->oldBullet) );
}

void Bullet::Init( const Vector2& initialPosition, const Vector2& initialVelocity ) {
	mPosition = initialPosition;
	mVelocity = initialVelocity;
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