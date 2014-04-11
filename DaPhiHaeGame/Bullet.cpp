#include "stdafx.h"
#include "Bullet.h"

#include "Sprite.h"
#include "SpriteBatcher.h"
#include "Asset.h"
#include "GameScene.h"

float Bullet::cSizeHalf = 5.f;

Bullet::Bullet( Vector2 initialPosition, Vector2 initialVelocity )
	: mPosition( initialPosition )
	, mVelocity( initialVelocity )
	, mSprite( new Sprite( Vector2( 0, 0 ), Vector2( cSizeHalf * 2, cSizeHalf * 2 ), gAsset->mainAtlas, *(gAsset->oldBullet) ) )
{
}

Bullet::~Bullet()
{
	SAFE_DELETE( mSprite );
}

void Bullet::Update( float deltaTime ) {
	mPosition += mVelocity * deltaTime;
	if ( mPosition.y < -cSizeHalf ) { 
		mPosition.y = GameScene::cWorldHeight + cSizeHalf;
		mPosition.x = static_cast<float>(rand() % 320);
	}
	mSprite->SetPosition( mPosition );
}

void Bullet::Render( SpriteBatcher* batcher ) const {
	batcher->DrawSprite( mSprite );
}