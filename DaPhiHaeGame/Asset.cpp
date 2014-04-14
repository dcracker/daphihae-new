#include "stdafx.h"
#include "Asset.h"

#include "SpriteAtlas.h"
#include "Camera2D.h"
#include "Rect.h"
#include "SpriteAnimation.h"

Asset::Asset()
	: mainAtlas( new SpriteAtlas( "Atlas.png" ) )
	, ship( mainAtlas->RegisterSprite( 0, Rect( 0, 20, 0, 16 ) ) )
	, oldBullet( mainAtlas->RegisterSprite( 1, Rect( 20, 30, 0, 10 ) ) )
	, roundBullet( mainAtlas->RegisterSprite( 2, Rect( 45, 60, 0, 15 ) ) )
	, arrowBullet( mainAtlas->RegisterSprite( 3, Rect( 30, 45, 0 ,15 ) ) )
	, animDead( new SpriteAnimation() )
{
	animDead->AddFrame( mainAtlas->RegisterSprite( 10, Rect( 0, 17, 17 * 1, 17 *  2 - 1 ) ), 0.033f );
	animDead->AddFrame( mainAtlas->RegisterSprite( 11, Rect( 0, 17, 17 * 2, 17 *  3 - 1 ) ), 0.033f );
	animDead->AddFrame( mainAtlas->RegisterSprite( 12, Rect( 0, 17, 17 * 3, 17 *  4 - 1 ) ), 0.033f );
	animDead->AddFrame( mainAtlas->RegisterSprite( 13, Rect( 0, 17, 17 * 4, 17 *  5 - 1 ) ), 0.033f );
	animDead->AddFrame( mainAtlas->RegisterSprite( 14, Rect( 0, 17, 17 * 5, 17 *  6 - 1 ) ), 0.033f );
	animDead->AddFrame( mainAtlas->RegisterSprite( 15, Rect( 0, 17, 17 * 6, 17 *  7 - 1 ) ), 0.033f );
	animDead->AddFrame( mainAtlas->RegisterSprite( 16, Rect( 0, 17, 17 * 7, 17 *  8 - 1 ) ), 0.033f );
	animDead->AddFrame( mainAtlas->RegisterSprite( 17, Rect( 0, 17, 17 * 8, 17 *  9 - 1 ) ), 0.033f );
	animDead->AddFrame( mainAtlas->RegisterSprite( 18, Rect( 0, 17, 17 * 9, 17 * 10 - 1 ) ), 0.033f );
}

Asset::~Asset()
{
	delete mainAtlas;
}

void Asset::Resume( const IFileIO* fileIO ) {
	mainAtlas->Load( fileIO );
}