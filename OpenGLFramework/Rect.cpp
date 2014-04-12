
#include "stdafx.h"

#include "Rect.h"

Rect::Rect() {
	SetRect( 0, 1, 0, 1 );
}
Rect::Rect( float left, float right, float bottom, float top ) {
	SetRect( left, right, bottom, top );
}

Rect::Rect( Vector2 center, Vector2 size ) {
	SetRect( center.x - size.x * 0.5f,	center.x + size.x * 0.5f,
			 center.y - size.y * 0.5f,	center.y + size.y * 0.5f );
}

Rect::~Rect() {
	// nothing
}

void Rect::SetRect( float left, float right, float bottom, float top ) {
	mLeft = left;
	mRight = right;
	mTop = top;
	mBottom = bottom;
}