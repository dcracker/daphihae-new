#pragma once

#include "TSingleton.hpp"

class IFileIO;
class SpriteAtlas;
class Rect;
class SpriteAnimation;
class BitmapFont;

#define gAsset Asset::getInstancePtr()

class Asset : public TSingleton<Asset>
{
public:
	Asset();
	~Asset();

	void Resume( const IFileIO* fileIO );

public:
	SpriteAtlas* const mainAtlas;
	BitmapFont* const font;
	BitmapFont* const boldFont;

	const unsigned int ship;
	const unsigned int oldBullet;
	const unsigned int roundBullet;
	const unsigned int arrowBullet;

	const unsigned int animDead;
};

