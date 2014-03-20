#pragma once

class Texture;
#include "Rect.h"

class Sprite {
public:
	Sprite( Vector2 size, const Texture* texture, Rect texCoord );
	Sprite( Vector2 position, Vector2 size, const Texture* texture, Rect texCoord );
	virtual ~Sprite();

	Vector2 GetPosition() const { return mPosition; }
	Vector2 GetSize() const { return mSize; }
	Rect GetTexCoord() const { return mTexCoord; }

	void SetPosition( Vector2 newPosition ) { mPosition = newPosition; }

private:
	void AdjustTexCoord( const Texture* texture, Rect texCoord );

private:
	Vector2 mPosition;
	Vector2 mSize;

	const Texture* mTexture;
	Rect mTexCoord;
};

