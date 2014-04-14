#include "stdafx.h"
#include "Ship.h"
#include "GameScene.h"
#include "Util.h"
#include "SpriteBatcher.h"
#include "Asset.h"
#include "SpriteAnimation.h"

const float Ship::cMoveSpeed = 300.f;
const float Ship::cWidthHalf = 10.f;

Ship::Ship()
	: mCurrentSpeed( 0 )
	, mCurrentPosition()
	, mCollider( mCurrentPosition, 3 )
	, mAlive( true )
	, mDeadAnim( new SpriteAnimation( *(gAsset->animDead) ) )
{
}


Ship::~Ship()
{
}

void Ship::Start( float initialPositionX, float initialPositionY ) {
	mCurrentPosition.x = initialPositionX;
	mCurrentPosition.y = initialPositionY;
	mAlive = true;
	mDeadAnim->Reset();
}

void Ship::SetMoveDirection( MoveDirection direction ) {
	mCurrentSpeed = (int)direction * cMoveSpeed;
}

bool Ship::CheckCollision( const CollisionCircle& bullet ) const {
	return mCollider.CheckCollision( bullet );
}

bool Ship::IsAlive() const {
	return mAlive;
}

void Ship::OnDead() {
	if ( IsAlive() == true ) {
		mAlive = false;
	}
}

void Ship::Update( float deltaTime ) {
	if ( IsAlive() == true ) {
		mCurrentPosition.x += mCurrentSpeed * deltaTime;
		mCurrentPosition.x = Util::Clamp( mCurrentPosition.x, cWidthHalf, static_cast<float>(GameScene::cWorldWidth) - cWidthHalf );
	}
	else {
		mDeadAnim->Update( deltaTime );
	}
}

void Ship::Render( SpriteBatcher* batcher ) const {
	if ( IsAlive() == true ) {
		batcher->DrawSprite( Rect( mCurrentPosition, Vector2( 20, 15 ) ), *(gAsset->ship) );
	//	mCollider.Render( batcher );
	}
	else {
		batcher->DrawSprite( Rect( mCurrentPosition, Vector2( 17, 17 ) ), *(mDeadAnim->GetCurrentFrame()) );
	}
}