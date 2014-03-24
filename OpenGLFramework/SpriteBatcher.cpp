
#include "stdafx.h"

#include "SpriteBatcher.h"
#include "Sprite.h"
#include "Rect.h"

SpriteBatcher::SpriteBatcher()
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

void SpriteBatcher::DrawSprite( Sprite* sprite ) {

	VertexFormat vertex[4];

	// position
	Vector2 position = sprite->GetPosition();
	Vector2 sizeHalf = sprite->GetSize() * 0.5f;

	vertex[0].position = Vector3( position.x - sizeHalf.x, position.y - sizeHalf.y, 0 );
	vertex[1].position = Vector3( position.x + sizeHalf.x, position.y - sizeHalf.y, 0 );
	vertex[2].position = Vector3( position.x + sizeHalf.x, position.y + sizeHalf.y, 0 );
	vertex[3].position = Vector3( position.x - sizeHalf.x, position.y + sizeHalf.y, 0 );

	// tex coord
	Rect texCoord = sprite->GetTexCoord();

	vertex[0].uv = Vector2( texCoord.GetLeft(),	 texCoord.GetTop() );
	vertex[1].uv = Vector2( texCoord.GetRight(), texCoord.GetTop() );
	vertex[2].uv = Vector2( texCoord.GetRight(), texCoord.GetBottom() );
	vertex[3].uv = Vector2( texCoord.GetLeft(),	 texCoord.GetBottom() );

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

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );

	// use &std::vector::front() instead of std::vector::data().
	// because gcc does not support that in ndk.
	glVertexPointer( 3, GL_FLOAT, sizeof(VertexFormat), &mVertices.front() );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(VertexFormat), ((float*)&mVertices.front()) + 3 );
	glDrawElements( GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_SHORT, &mIndices.front() );

	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );
}
