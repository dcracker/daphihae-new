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

	const Rect* const ship;
	const Rect* const oldBullet;
	const Rect* const roundBullet;
	const Rect* const arrowBullet;

	SpriteAnimation* const animDead;
};

