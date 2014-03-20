#ifndef OpenGLTest_H_
#define OpenGLTest_H_

#include <vector>
#include "Interfaces/IGame.h"

class IPlatform;
class Texture;
class SpriteBatcher;
class Sprite;
class Camera;
class Camera2D;

class OpenGLTest : public IGame {
public:
	OpenGLTest( IPlatform* platformInstance );
	~OpenGLTest();
	
	void Resume();
	void Pause();
	void Update( float deltaTime );
	void Render() const;

private:
	IPlatform* 	mPlatform;
	GLfloat 	mAngle;
	Texture*	mTestTexture;
	SpriteBatcher* mSpriteBatcher;

	std::vector<Sprite*> mBullets;

	Camera*		mCamera;
	Camera2D*	m2dCam;
};

#endif	// OpenGLTest_H_
