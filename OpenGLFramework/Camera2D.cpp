#include "stdafx.h"
#include "Camera2D.h"

Camera2D::Camera2D( float left, float right, float bottom, float top )
	: mDrawRegion( left, right, bottom, top )
	, mNear( 1 )
	, mFar( -1 )
{
}

Camera2D::Camera2D( Rect region )
	: mDrawRegion( region )
	, mNear( 1 )
	, mFar( -1 )
{
}


Camera2D::~Camera2D()
{
}

void Camera2D::Bind() const {
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( mDrawRegion.GetLeft(), mDrawRegion.GetRight(), mDrawRegion.GetBottom(), mDrawRegion.GetTop(), mNear, mFar );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}