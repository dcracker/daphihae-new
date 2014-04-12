#pragma once

#include <vector>
#include "glmtypedef.h"
#include "Common/CommonHeaders.h"
#include "Rect.h"

class Texture;
class Sprite;

class SpriteBatcher
{
public:
	SpriteBatcher();
	~SpriteBatcher();

	void Clear();
	void DrawSprite( Rect position, Rect texCoord );
	void Render() const;

private:
	struct VertexFormat {
		Vector2 position;
		Vector2 uv;
	};

	std::vector<VertexFormat> mVertices;
	std::vector<GLushort> mIndices;
	int mNumSprite;
};
