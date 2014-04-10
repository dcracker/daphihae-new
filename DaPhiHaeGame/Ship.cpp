#include "stdafx.h"
#include "Ship.h"
#include "GameScene.h"
#include "Util.h"
#include "Sprite.h"
#include "SpriteBatcher.h"
#include "Asset.h"

const float Ship::cMoveSpeed = 300.f;
const float Ship::cWidthHalf = 10.f;

Ship::Ship( float initialPositionX, float initialPositionY )
	: mCurrentSpeed( 0 )
	, mCurrentPosition( initialPositionX, initialPositionY )
	, mSprite( NULL )
{
}


Ship::~Ship()
{
	SAFE_DELETE( mSprite );
}

void Ship::SetMoveDirection( MoveDirection direction ) {
	mCurrentSpeed = (int)direction * cMoveSpeed;
}

void Ship::Resume() {
	if ( mSprite == NULL ) {
		mSprite = new Sprite( Vector2( 0, 0 ), Vector2( 20, 15 ), gAsset->mainAtlas, *(gAsset->ship) );
	}
}

void Ship::Update( float deltaTime ) {
	mCurrentPosition.x += mCurrentSpeed * deltaTime;
	mCurrentPosition.x = Util::Clamp( mCurrentPosition.x, cWidthHalf, static_cast<float>(GameScene::cWorldWidth) - cWidthHalf );

	mSprite->SetPosition( mCurrentPosition );
}

void Ship::Render( SpriteBatcher* batcher ) const {
	if ( mSprite == NULL ) {
		return;
	}

	batcher->DrawSprite( mSprite );
}