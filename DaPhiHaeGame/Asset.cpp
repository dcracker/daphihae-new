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
{
	unsigned int frames[] = {
		mainAtlas->RegisterSprite( Rect( 0, 17, 17 * 1, 17 *  2 - 1 ) ),
		mainAtlas->RegisterSprite( Rect( 0, 17, 17 * 2, 17 *  3 - 1 ) ),
		mainAtlas->RegisterSprite( Rect( 0, 17, 17 * 3, 17 *  4 - 1 ) ),
		mainAtlas->RegisterSprite( Rect( 0, 17, 17 * 4, 17 *  5 - 1 ) ),
		mainAtlas->RegisterSprite( Rect( 0, 17, 17 * 5, 17 *  6 - 1 ) ),
		mainAtlas->RegisterSprite( Rect( 0, 17, 17 * 6, 17 *  7 - 1 ) ),
		mainAtlas->RegisterSprite( Rect( 0, 17, 17 * 7, 17 *  8 - 1 ) ),
		mainAtlas->RegisterSprite( Rect( 0, 17, 17 * 8, 17 *  9 - 1 ) ),
		mainAtlas->RegisterSprite( Rect( 0, 17, 17 * 9, 17 * 10 - 1 ) )
	};
	animDead = mainAtlas->RegisterAnimation( 0.033f, 9, frames );
}

Asset::~Asset()
{
	delete mainAtlas;
}

void Asset::Resume( const IFileIO* fileIO ) {
	mainAtlas->Load( fileIO );
}