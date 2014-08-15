#include "stdafx.h"
#include "Asset.h"

#include "SpriteAtlas.h"
#include "BitmapFont.h"

Asset::Asset()
	: mainAtlas( new SpriteAtlas( "Atlas.png" ) )
	, ship( mainAtlas->RegisterSprite( 0, 0, 20, 16 ) )
	, oldBullet( mainAtlas->RegisterSprite( 20, 0, 30, 10 ) )
	, roundBullet( mainAtlas->RegisterSprite( 45, 0, 60, 15 ) )
	, arrowBullet( mainAtlas->RegisterSprite( 30, 0, 45, 15 ) )
	, animDead( mainAtlas->RegisterAnimation( 0.033f, 0, 16, 153, 33, Vector2( 17, 17 ) ) )
	, title( mainAtlas->RegisterSprite( 0, 128, 61, 148 ) )
	//, font( new BitmapFont( "Ascii.fnt", mainAtlas, 0, 33 ) )
	, boldFont( new BitmapFont( "Ascii_bold.fnt", mainAtlas, 0, 33 ) )
{
}

Asset::~Asset()
{
	delete mainAtlas;
}

void Asset::Resume( const IFileIO* fileIO ) {
	mainAtlas->Load( fileIO );
}