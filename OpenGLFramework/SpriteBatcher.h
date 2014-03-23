#pragma once

#include <vector>
#include "glmtypedef.h"
#include "Common/CommonHeaders.h"

class Texture;
class Sprite;

class SpriteBatcher
{
public:
	SpriteBatcher();
	~SpriteBatcher();

	void Clear();
	void DrawSprite( Sprite* sprite );
	void Render() const;

private:
	struct VertexFormat {
		Vector3 position;
		Vector2 uv;
	};

	std::vector<VertexFormat> mVertices;
	std::vector<GLushort> mIndices;
	int mNumSprite;
};
