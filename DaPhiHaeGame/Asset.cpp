#include "stdafx.h"
#include "Asset.h"

#include "SpriteAtlas.h"
#include "Camera2D.h"
#include "Rect.h"

Asset::Asset()
	: mainAtlas( new SpriteAtlas( "Atlas.png" ) )
	, ship( mainAtlas->RegisterSprite( 0, Rect( 0, 20, 0, 16 ) ) )
	, oldBullet( mainAtlas->RegisterSprite( 1, Rect( 20, 30, 0, 10 ) ) )
	, roundBullet( mainAtlas->RegisterSprite( 2, Rect( 45, 60, 0, 15 ) ) )
	, arrowBullet( mainAtlas->RegisterSprite( 3, Rect( 30, 45, 0 ,15 ) ) )
{
}

Asset::~Asset()
{
	delete mainAtlas;
}

void Asset::Resume( const IFileIO* fileIO ) {
	mainAtlas->Load( fileIO );
}