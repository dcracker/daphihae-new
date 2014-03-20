#pragma once
#include "Rect.h"

class Camera
{
public:
	Camera( float fovY, float aspectRatio, float _near, float _far );
	~Camera();

	void Bind() const;

	void SetAspectRatio( float aspectRatio ) { mAspectRatio = aspectRatio; }
	void SetFov( float fovY ) { mFov = fovY; }

private:
	float mFov;
	float mAspectRatio;
	float mNear;
	float mFar;
};

