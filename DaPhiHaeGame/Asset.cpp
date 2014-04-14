#include "stdafx.h"
#include "Asset.h"

#include "SpriteAtlas.h"
#include "Camera2D.h"
#include "Rect.h"
#include "SpriteAnimation.h"

Asset::Asset()
	: mainAtlas( new SpriteAtlas( "Atlas.png" ) )
	, ship( mainAtlas->RegisterSprite( Rect( 0, 20, 0, 16 ) ) )
	, oldBullet( mainAtlas->RegisterSprite( Rect( 20, 30, 0, 10 ) ) )
	, roundBullet( mainAtlas->RegisterSprite( Rect( 45, 60, 0, 15 ) ) )
	, arrowBullet( mainAtlas->RegisterSprite( Rect( 30, 45, 0 ,15 ) ) )
	, animDead( mainAtlas->RegisterAnimation( 0.033f, Rect( 0, 17, 16, 169 ), Vector2( 17, 17 ) ) )
{
}

Asset::~Asset()
{
	delete mainAtlas;
}

void Asset::Resume( const IFileIO* fileIO ) {
	mainAtlas->Load( fileIO );
}