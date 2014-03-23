
#include "stdafx.h"

#include "Sprite.h"
#include "Texture.h"
#include "Rect.h"

Sprite::Sprite( Vector2 size, const Texture* texture, Rect texCoord )
	: mPosition()
	, mSize( size )
	, mTexture( texture )
	, mTexCoord()
{
	AdjustTexCoord( texture, texCoord );
}
Sprite::Sprite( Vector2 position, Vector2 size, const Texture* texture, Rect texCoord )
	: mPosition( position )
	, mSize( size )
	, mTexture( texture )
	, mTexCoord()
{
	AdjustTexCoord( texture, texCoord );
}

Sprite::~Sprite()
{
	mTexture = NULL;
}

void Sprite::AdjustTexCoord( const Texture* texture, Rect texCoord ) {

	float texWidth = static_cast<float>(texture->GetWidth());
	float texHeight = static_cast<float>(texture->GetHeight());

	mTexCoord.SetRect(	texCoord.GetLeft() / texWidth,
						texCoord.GetRight()	/ texWidth,
						texCoord.GetTop() / texHeight,
						texCoord.GetBottom() / texHeight );
}