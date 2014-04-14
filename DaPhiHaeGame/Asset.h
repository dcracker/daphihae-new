#pragma once

#include "TSingleton.hpp"

class IFileIO;
class SpriteAtlas;
class Rect;
class SpriteAnimation;

#define gAsset Asset::getInstancePtr()

class Asset : public TSingleton<Asset>
{
public:
	Asset();
	~Asset();

	void Resume( const IFileIO* fileIO );

public:
	SpriteAtlas* const mainAtlas;

	const unsigned int ship;
	const unsigned int oldBullet;
	const unsigned int roundBullet;
	const unsigned int arrowBullet;

	const unsigned int animDead;
};

