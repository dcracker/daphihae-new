#include "stdafx.h"
#include "Ship.h"
#include "GameScene.h"
#include "Util.h"
#include "SpriteBatcher.h"
#include "Asset.h"

const float Ship::cMoveSpeed = 300.f;
const float Ship::cWidthHalf = 10.f;

Ship::Ship( float initialPositionX, float initialPositionY )
	: mCurrentSpeed( 0 )
	, mCurrentPosition( initialPositionX, initialPositionY )
	, mCollider( mCurrentPosition, 3 )
	, mAlive( true )
{
}


Ship::~Ship()
{
}

void Ship::SetMoveDirection( MoveDirection direction ) {
	mCurrentSpeed = (int)direction * cMoveSpeed;
}

bool Ship::CheckCollision( const CollisionCircle& bullet ) const {
	return mCollider.CheckCollision( bullet );
}

void Ship::OnDead() {
	mAlive = false;
}

void Ship::Update( float deltaTime ) {
	if ( mAlive == false ) {
		return;
	}

	mCurrentPosition.x += mCurrentSpeed * deltaTime;
	mCurrentPosition.x = Util::Clamp( mCurrentPosition.x, cWidthHalf, static_cast<float>(GameScene::cWorldWidth) - cWidthHalf );
}

void Ship::Render( SpriteBatcher* batcher ) const {
	if ( mAlive == false ) {
		return;
	}

	batcher->DrawSprite( Rect( mCurrentPosition, Vector2( 20, 15 ) ), *(gAsset->ship) );
//	mCollider.Render( batcher );
}