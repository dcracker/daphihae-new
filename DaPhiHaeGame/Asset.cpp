#include "stdafx.h"
#include "Asset.h"

#include "SpriteAtlas.h"
#include "Camera2D.h"
#include "Rect.h"
#include "SpriteAnimation.h"

Asset::Asset()
	: mainAtlas( new SpriteAtlas( "Atlas.png" ) )
	, ship( mainAtlas->RegisterSprite( 0, 0, 20, 16 ) )
	, oldBullet( mainAtlas->RegisterSprite( 20, 0, 30, 10 ) )
	, roundBullet( mainAtlas->RegisterSprite( 45, 0, 60, 15 ) )
	, arrowBullet( mainAtlas->RegisterSprite( 30, 0, 45, 15 ) )
	, animDead( mainAtlas->RegisterAnimation( 0.033f, 0, 16, 153, 33, Vector2( 17, 17 ) ) )
	, font( mainAtlas->RegisterBitmapFont( 0, 33, 100, 51, Vector2( 10, 18 ) ) )
{
}

Asset::~Asset()
{
	delete mainAtlas;
}

void Asset::Resume( const IFileIO* fileIO ) {
	mainAtlas->Load( fileIO );
}