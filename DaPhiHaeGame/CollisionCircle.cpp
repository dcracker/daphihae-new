#include "stdafx.h"
#include "CollisionCircle.h"
#include "glm/gtx/norm.hpp"

#include "SpriteBatcher.h"
#include "Asset.h"

CollisionCircle::CollisionCircle( const Vector2& parentPosition, float radius )
	: mPosition( parentPosition )
	, mRadius( radius )
{
}


CollisionCircle::~CollisionCircle()
{
}

bool CollisionCircle::CheckCollision( const CollisionCircle& subject ) const {
	float distanceSq = glm::distance2( mPosition, subject.mPosition );
	float radiusSum = mRadius + subject.mRadius;
	return distanceSq <= radiusSum * radiusSum;
}

void CollisionCircle::Render( SpriteBatcher* batcher ) const {
	Rect position( mPosition, Vector2( mRadius * 2, mRadius * 2 ) );
//	batcher->DrawSprite( position, *(gAsset->roundBullet) );
}