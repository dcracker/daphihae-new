#pragma once

#include "TSingleton.hpp"

class IFileIO;
class Texture;
class Rect;

#define gAsset Asset::getInstancePtr()

class Asset : public TSingleton<Asset>
{
public:
	Asset( const IFileIO* fileIO );
	~Asset();

	void Resume();

public:
	Texture* const mainAtlas;
	const Rect* const ship;
	const Rect* const oldBullet;
	const Rect* const roundBullet;
	const Rect* const arrowBullet;
};

