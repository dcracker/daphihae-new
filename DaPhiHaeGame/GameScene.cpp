#include "stdafx.h"
#include "GameScene.h"

#include "Interfaces/IPlatform.h"
#include "Asset.h"
#include "SpriteBatcher.h"
#include "Sprite.h"
#include "Camera2D.h"

#include "Texture.h"

GameScene::GameScene( IPlatform* platform )
	: mPlatform( platform )
	, mMainCam( new Camera2D( 0, 320, 0, 480 ) )
	, mSpriteBatcher( new SpriteBatcher() )
	, mShip( NULL )
	, mShipSpeed( 0 )
{
	mBullets.clear();
}

GameScene::~GameScene()
{
	SAFE_DELETE( mMainCam );
	SAFE_DELETE( mSpriteBatcher );
	SAFE_DELETE( mShip );
	for ( int i=mBullets.size()-1; i >= 0; --i ) {
		SAFE_DELETE( mBullets[i] );
	}
}

void GameScene::Resume() {
	glDisable(GL_DITHER);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glClearColor(0, 0, 0, 0);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    
	const IGraphics* graphics = mPlatform->GetGraphics();
    glViewport(0, 0, graphics->GetWidth(), graphics->GetHeight());

    glEnable(GL_TEXTURE_2D);
}

void GameScene::Pause() {

}

void GameScene::Update( float deltaTime ) {

	ProcessTouchInput();
	UpdateShip( deltaTime );
	UpdateBullets( deltaTime );
	BatchSprites();
	CheckCollision();
}

void GameScene::Render() const {
    glClear( GL_COLOR_BUFFER_BIT );
	gAsset->mainAtlas->Bind();
	mMainCam->Bind();
	mSpriteBatcher->Render();
}

void GameScene::ProcessTouchInput() {
	if ( mPlatform->GetInput()->IsTouchDown( 0 ) == false ) {
		mShipSpeed = 0;
		return;
	}

	int x = mPlatform->GetInput()->GetTouchX( 0 );
	int w = mPlatform->GetGraphics()->GetWidth();
	float touchPoint = (float)x / (float)w;

	static const float cShipSpeed = 100.f;
	if ( touchPoint > 0.5f ) {
		mShipSpeed = cShipSpeed;
	}
	else {
		mShipSpeed = -cShipSpeed;
	}
}

void GameScene::UpdateShip( float deltaTime ) {
	if ( mShip == NULL ) {
		mShip = new Sprite( Vector2( 160, 20 ), Vector2( 20, 15 ), gAsset->mainAtlas, *(gAsset->ship) );
	}

	Vector2 currentPosition = mShip->GetPosition();
	currentPosition.x += mShipSpeed * deltaTime;
	mShip->SetPosition( currentPosition );
}

void GameScene::UpdateBullets( float deltaTime ) {
	static const float speed = -100;
	for( std::vector<Sprite*>::iterator it = mBullets.begin(); it != mBullets.end(); ++it ) {
		Vector2 currentPosition = (*it)->GetPosition();
		currentPosition.y += speed * deltaTime;
		float halfHeight = (*it)->GetSize().y * 0.5f;
		if ( currentPosition.y < -halfHeight ) {
			currentPosition.y = 480 + halfHeight;
			currentPosition.x = static_cast<float>(rand() % 320);
		}
		(*it)->SetPosition( currentPosition );
	}

	static float elapsedTime = 0;
	static const float size = 10;
	elapsedTime += deltaTime;
	if ( mBullets.size() < 100 && elapsedTime > 1 ) {
		elapsedTime -= 1;
		mBullets.push_back( new Sprite( Vector2( rand() % 320, 480 + size * 0.5f ), Vector2( size, size ), gAsset->mainAtlas, *(gAsset->oldBullet) ) );
	}
}

void GameScene::BatchSprites() {
	mSpriteBatcher->Clear();
	for( std::vector<Sprite*>::iterator it = mBullets.begin(); it != mBullets.end(); ++it ) {
		mSpriteBatcher->DrawSprite( *it );
	}
	mSpriteBatcher->DrawSprite( mShip );
}

void GameScene::CheckCollision() {

}