
#include "stdafx.h"

#include "Interfaces/IPlatform.h"
#include "Texture.h"
#include "SpriteBatcher.h"
#include "Sprite.h"
#include "Rect.h"
#include "Camera.h"
#include "Camera2D.h"

#include "logger.h"

#include "OpenGLTest.h"

#define LOG_TAG "OpenGLTest"

static GLfloat vertices[][3] = {
		// front
		{ -1, -1, +1 },
		{ +1, -1, +1 },
		{ +1, +1, +1 },
		{ -1, +1, +1 },

		// back
		{ -1, -1, -1 },
		{ -1, +1, -1 },
		{ +1, +1, -1 },
		{ +1, -1, -1 },

		// top
		{ -1, +1, -1 },
		{ -1, +1, +1 },
		{ +1, +1, +1 },
		{ +1, +1, -1 },

		// bottom
		{ -1, -1, -1 },
		{ +1, -1, -1 },
		{ +1, -1, +1 },
		{ -1, -1, +1 },

		// right
		{ +1, -1, -1 },
		{ +1, +1, -1 },
		{ +1, +1, +1 },
		{ +1, -1, +1 },

		// left
		{ -1, -1, -1 },
		{ -1, -1, +1 },
		{ -1, +1, +1 },
		{ -1, +1, -1 },
};

static GLfloat uvs[][2] = {
	{ 0, 0 },
	{ 2, 0 },
	{ 2, 2 },
	{ 0, 2 },

	{ 1, 0 },
	{ 1, 1 },
	{ 0, 1 },
	{ 0, 0 },

	{ 0, 1 },
	{ 0, 0 },
	{ 1, 0 },
	{ 1, 1 },

	{ 1, 1 },
	{ 0, 1 },
	{ 0, 0 },
	{ 1, 0 },

	{ 1, 0 },
	{ 1, 1 },
	{ 0, 1 },
	{ 0, 0 },

	{ 0, 0 },
	{ 1, 0 },
	{ 1, 1 },
	{ 0, 1 },

	{ 0, 0 },
	{ 1, 0 },
	{ 1, 1 },
	{ 0, 1 },
};

GLubyte indices[] = {
     0,  2,  1,		 0,  3,  2,
     4,  6,  5,		 4,  7,  6,
     8, 10,  9,		 8, 11, 10,
    12, 14, 13,		12, 15, 14,
    16, 18, 17,		16, 19, 18,
    20, 22, 21,		20, 23, 22,
};

OpenGLTest::OpenGLTest( IPlatform* platformInstance )
	: mPlatform( platformInstance )
	, mAngle( 0 )
	, mTestTexture( new Texture( platformInstance->GetFileIO(), "test.png" ) )
	, mSpriteBatcher( new SpriteBatcher() )
	, mCamera( NULL )
	, m2dCam( NULL )
{
	mTestTexture->SetFilter( GL_LINEAR );
	mTestTexture->SetWrapMode( GL_REPEAT );

	m2dCam = new Camera2D( 0.f, 320.f, 0.f, 480.f );
	mCamera = new Camera( 90.f, 1.f, 1.f, 10.f );
//	mBullets.push_back( new Sprite( Vector2( 320 / 2, 480 / 2 ), Vector2( 10, 10 ), mTestTexture, Vector2( 0, 0 ), Vector2( 512, 512 ) ) );
}

OpenGLTest::~OpenGLTest() {
	SAFE_DELETE( mTestTexture );
	SAFE_DELETE( mSpriteBatcher );
}

void OpenGLTest::Resume() {

	glDisable(GL_DITHER);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glClearColor(0, 0, 0, 1);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    
	const IGraphics* graphics = mPlatform->GetGraphics();
    glViewport(0, 0, graphics->GetWidth(), graphics->GetHeight());

    glEnable(GL_TEXTURE_2D);
    mTestTexture->Load();

    mCamera->SetAspectRatio( graphics->GetAspectRatio() );
}

void OpenGLTest::Pause() {
	// do nothing yet
}

void OpenGLTest::Update( float deltaTime ) {
//	static int time = 10;
	static float speed = -100;
    mAngle -= 360 * deltaTime / (mPlatform->GetInput()->IsTouchDown(0) ? 60 : 5);

	mSpriteBatcher->Clear();
	for( std::vector<Sprite*>::iterator it = mBullets.begin(); it != mBullets.end(); ++it ) {
		Vector2 currentPosition = (*it)->GetPosition();
		currentPosition.y += speed * deltaTime;
		if ( currentPosition.y < 0 ) {
			currentPosition.y = 480;
		}
		(*it)->SetPosition( currentPosition );
		mSpriteBatcher->DrawSprite( *it );
	}
	
	static float elapsedTime = 0;
	elapsedTime += deltaTime;
	if ( mBullets.size() < 100 && elapsedTime > 1 ) {
		elapsedTime -= 1;
		mBullets.push_back( new Sprite( Vector2( rand() % 320, 480 ), Vector2( 50, 50 ), mTestTexture, Rect( 0, 512, 0, 512 ) ) );
	}
}

void OpenGLTest::Render() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mCamera->Bind();

    mTestTexture->Bind();

    glEnable(GL_DEPTH_TEST);
    glTranslatef(0, 0, -3.0f);
    glRotatef(mAngle, 0, 1, 0);
    glRotatef(mAngle*0.25f, 1, 0, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glFrontFace(GL_CW);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, uvs);

    glColor4f( 1, 1, 1, 1 );
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	m2dCam->Bind();
	glFrontFace( GL_CCW );
	glDisable( GL_DEPTH_TEST );
	glLoadIdentity();
	mSpriteBatcher->Render();
}
