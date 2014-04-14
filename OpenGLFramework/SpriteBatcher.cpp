#include "stdafx.h"
#include "SpriteBatcher.h"

#include "SpriteAtlas.h"
#include "Rect.h"

SpriteBatcher::SpriteBatcher( const SpriteAtlas* atlas )
	: mAtlas( atlas )
{
	Clear();
}

SpriteBatcher::~SpriteBatcher()
{
	Clear();
}

void SpriteBatcher::Clear() {
	mNumSprite = 0;
	mVertices.clear();
	mIndices.clear();
}

void SpriteBatcher::DrawSprite( Rect position, unsigned int spriteHandle ) {
	DrawSprite( position, mAtlas->GetSpriteCoord( spriteHandle ) );
}

void SpriteBatcher::DrawSprite( Rect position, unsigned int animationHandle, float frameTime ) {
	DrawSprite( position, mAtlas->GetAnimationFrame( animationHandle, frameTime ) );
}

void SpriteBatcher::DrawSprite( Rect position, Rect texCoord ) {

	VertexFormat vertex[4];
	
	vertex[0].position = Vector2( position.GetLeft(),	position.GetBottom() );
	vertex[1].position = Vector2( position.GetRight(),	position.GetBottom() );
	vertex[2].position = Vector2( position.GetRight(),	position.GetTop() );
	vertex[3].position = Vector2( position.GetLeft(),	position.GetTop() );

	vertex[0].uv = Vector2( texCoord.GetLeft(),	 texCoord.GetBottom() );
	vertex[1].uv = Vector2( texCoord.GetRight(), texCoord.GetBottom() );
	vertex[2].uv = Vector2( texCoord.GetRight(), texCoord.GetTop() );
	vertex[3].uv = Vector2( texCoord.GetLeft(),	 texCoord.GetTop() );

	for ( int i=0; i < 4; ++i ) {
		mVertices.push_back(vertex[i]);
	}

	// index
	mIndices.push_back( mNumSprite * 4 + 0 );
	mIndices.push_back( mNumSprite * 4 + 1 );
	mIndices.push_back( mNumSprite * 4 + 2 );

	mIndices.push_back( mNumSprite * 4 + 0 );
	mIndices.push_back( mNumSprite * 4 + 2 );
	mIndices.push_back( mNumSprite * 4 + 3 );

	++mNumSprite;
}

void SpriteBatcher::Render() const {
	if ( mNumSprite <= 0 ) {
		return; 
	}

	mAtlas->Bind();

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	// use &std::vector::front() instead of std::vector::data().
	// because gcc does not support that in ndk.
	glVertexPointer( 2, GL_FLOAT, sizeof(VertexFormat), &mVertices.front() );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(VertexFormat), ((float*)&mVertices.front()) + 2 );
	glDrawElements( GL_TRIANGLES, (int)mIndices.size(), GL_UNSIGNED_SHORT, &mIndices.front() );

	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
}
