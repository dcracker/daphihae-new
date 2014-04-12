#include "stdafx.h"
#include "Asset.h"

#include "Camera2D.h"
#include "Texture.h"
#include "Rect.h"

Asset::Asset( const IFileIO* fileIO )
	: mainAtlas( new Texture( fileIO, "Atlas.png" ) )
	, ship( new Rect( 0, 0.0390625f, 0, 0.03125f ) )
	, oldBullet( new Rect( 0.0390625f, 0.05859375f, 0, 0.01953125f ) )
	, roundBullet( new Rect( 0.087890625f, 0.1171875, 0, 0.029296875f ) )
	, arrowBullet( new Rect( 0.05859375f, 0.087890625f, 0, 0.029296875f ) )
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