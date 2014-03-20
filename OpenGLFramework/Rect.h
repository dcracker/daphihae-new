#pragma once
#include "glm/vec2.hpp"
#include "glmtypedef.h"

class Rect {
public:
	Rect();
	Rect( float left, float right, float bottom, float top );
	Rect( Vector2 center, Vector2 size );
	~Rect();

	float GetLeft() const	{ return mLeft;	}
	float GetRight() const	{ return mRight; }
	float GetTop() const	{ return mTop; }
	float GetBottom() const { return mBottom; }
	float GetWidth() const	{ return mRight - mLeft; }
	float GetHeight() const { return mTop - mBottom; }

	void SetRect( float left, float right, float bottom, float top );

private:
	float mLeft;
	float mRight;
	float mTop;
	float mBottom;
};