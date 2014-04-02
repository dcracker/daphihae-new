#pragma once
#include "Rect.h"

class Camera2D
{
public:
	Camera2D( float left, float right, float bottom, float top );
	Camera2D( Rect region );
	~Camera2D();

	void Bind() const;
	Vector2 AdjustTouchPoint( const Vector2 touchedPoint ) const;

private:
	Rect mDrawRegion;
	float mNear;
	float mFar;
};

