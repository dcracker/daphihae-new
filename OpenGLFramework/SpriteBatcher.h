#pragma once

#include <vector>
#include "glmtypedef.h"
#include "Common/CommonHeaders.h"
#include "Rect.h"

class SpriteAtlas;

class SpriteBatcher
{
public:
	SpriteBatcher( const SpriteAtlas* atlas );
	~SpriteBatcher();

	void Clear();
	void DrawSprite( Rect position, unsigned int spriteHandle );
	void DrawSprite( Rect position, unsigned int animationHandle, float frameTime );
	void Render() const;

private:
	void DrawSprite( Rect position, Rect texCoord );

private:
	struct VertexFormat {
		Vector2 position;
		Vector2 uv;
	};

	std::vector<VertexFormat> mVertices;
	std::vector<GLushort> mIndices;
	int mNumSprite;
	const SpriteAtlas* const mAtlas;
};
