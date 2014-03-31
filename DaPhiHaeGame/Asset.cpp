#include "stdafx.h"
#include "Asset.h"

#include "Camera2D.h"
#include "Texture.h"
#include "Rect.h"

Asset::Asset( const IFileIO* fileIO )
	: mainAtlas( new Texture( fileIO, "Atlas.png" ) )
	, ship( new Rect( 0, 20, 0, 16 ) )
	, oldBullet( new Rect( 20, 30, 0, 10 ) )
	, roundBullet( new Rect( 45, 60, 0, 15 ) )
	, arrowBullet( new Rect( 30, 45, 0, 15 ) )
{
}

Asset::~Asset()
{
	delete mainAtlas;
	delete ship;
	delete oldBullet;
	delete roundBullet;
	delete arrowBullet;
}

void Asset::Resume() {
	mainAtlas->Load();
}