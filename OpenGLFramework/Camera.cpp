#include "stdafx.h"
#include "Camera.h"


Camera::Camera( float fovY, float aspectRatio, float _near, float _far )
	: mFov( fovY )
	, mAspectRatio( aspectRatio )
	, mNear( _near )
	, mFar( _far )
{
}


Camera::~Camera()
{
}

void Camera::Bind() const {
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	float h = tan( mFov / 2 * DEG_TO_RAD ) * mNear;
	float w = h * mAspectRatio;
	glFrustum( -w, w, -h, h, mNear, mFar );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
}
