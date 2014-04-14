#include "stdafx.h"
#include "Ship.h"
#include "GameScene.h"
#include "Util.h"
#include "SpriteBatcher.h"
#include "Asset.h"
#include "SpriteAnimation.h"
#include "SpriteAtlas.h"

const float Ship::cMoveSpeed = 300.f;
const float Ship::cWidthHalf = 10.f;

Ship::Ship()
	: mCurrentSpeed( 0 )
	, mCurrentPosition()
	, mCollider( mCurrentPosition, 3 )
	, mDeadAnimCounter( -1 )
{
}


Ship::~Ship()
{
}

void Ship::Start( float initialPositionX, float initialPositionY ) {
	mCurrentPosition.x = initialPositionX;
	mCurrentPosition.y = initialPositionY;
	mDeadAnimCounter = -1;
}

void Ship::SetMoveDirection( MoveDirection direction ) {
	mCurrentSpeed = (int)direction * cMoveSpeed;
}

bool Ship::CheckCollision( const CollisionCircle& bullet ) const {
	return mCollider.CheckCollision( bullet );
}

bool Ship::IsAlive() const {
	return mDeadAnimCounter < 0;
}

void Ship::OnDead() {
	if ( IsAlive() == true ) {
		mDeadAnimCounter = 0;
	}
}

void Ship::Update( float deltaTime ) {
	if ( IsAlive() == true ) {
		mCurrentPosition.x += mCurrentSpeed * deltaTime;
		mCurrentPosition.x = Util::Clamp( mCurrentPosition.x, cWidthHalf, static_cast<float>(GameScene::cWorldWidth) - cWidthHalf );
	}
	else {
		mDeadAnimCounter += deltaTime;
	}
}

void Ship::Render( SpriteBatcher* batcher ) const {
	if ( IsAlive() == true ) {
		batcher->DrawSprite( Rect( mCurrentPosition, Vector2( 20, 15 ) ), gAsset->mainAtlas->GetSpriteCoord( gAsset->ship ) );
	//	mCollider.Render( batcher );
	}
	else {
		batcher->DrawSprite( Rect( mCurrentPosition, Vector2( 17, 17 ) ), gAsset->mainAtlas->GetAnimationFrame( gAsset->animDead, mDeadAnimCounter ) );
	}
}