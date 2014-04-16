#include "stdafx.h"
#include "GameScene.h"

#include "Interfaces/IPlatform.h"
#include "Asset.h"
#include "SpriteBatcher.h"
#include "Camera2D.h"

#include "Ship.h"
#include "BulletSpawner.h"
#include "BulletPool.h"
#include "Util.h"

GameScene::GameScene( IPlatform* platform )
	: mPlatform( platform )
	, mMainCam( new Camera2D( 0, static_cast<float>(cWorldWidth), 0, static_cast<float>(cWorldHeight) ) )
	, mSpriteBatcher( new SpriteBatcher( gAsset->mainAtlas ) )
	, mShip( new Ship() )
	, mBulletPool( new BulletPool() )
{
	mSpawners.clear();
	mSpawners.push_back( new BulletSpawner( 0.1f, Vector2( 0, -300 ) ) );
	mSpawners.push_back( new BulletSpawner( 0.5f, Vector2( 0, -700 ) ) );
	RestartGame();
}

GameScene::~GameScene()
{
	SAFE_DELETE( mMainCam );
	SAFE_DELETE( mSpriteBatcher );
	SAFE_DELETE( mShip );

	foreach ( BulletSpawner*, it, mSpawners ) {
		delete *it;
	}
	mSpawners.clear();

	SAFE_DELETE( mBulletPool );
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
	mShip->Update( deltaTime );
	UpdateBullets( deltaTime );
	CheckCollision();
	BatchSprites();
}

void GameScene::Render() const {
    glClear( GL_COLOR_BUFFER_BIT );
	mMainCam->Bind();
	mSpriteBatcher->Render();
}

void GameScene::RestartGame() {
	mShip->Start( static_cast<float>(cWorldWidth * 0.5f), 100.f );
	foreach ( BulletSpawner*, it, mSpawners ) {
		(*it)->Reset();
	}
}

void GameScene::ProcessTouchInput() {
	if ( mShip->IsAlive() == true ) {
		ProcessInputForMove();
	}
	else {
		ProcessInputForRestart();
	}
}

void GameScene::ProcessInputForMove() {
	bool left = false;
	bool right = false;

	for ( int i=0; i < cMaxNumFingers; ++i ) {
		if ( mPlatform->GetInput()->IsTouchDown( i ) == false ) {
			continue;
		}

		int x = mPlatform->GetInput()->GetTouchX( i );
		int w = mPlatform->GetGraphics()->GetWidth();
		float touchPoint = (float)x / (float)w;

		// right side touched
		if ( touchPoint > 0.5f ) {
			right = true;
		}
		// left side touched
		else {
			left = true;
		}
	}

	Ship::MoveDirection moveDirection = Ship::NEUTRAL;
	if ( left != right ) {
		moveDirection = (left == true) ? Ship::LEFT : Ship::RIGHT;
	}
	mShip->SetMoveDirection( moveDirection );
}

void GameScene::ProcessInputForRestart() {
	static bool oldTouch = true;
	bool touched = mPlatform->GetInput()->IsTouchDown( 0 );

	if ( oldTouch == false && touched == true ) {
		RestartGame();
	}

	oldTouch = touched;
}

void GameScene::UpdateBullets( float deltaTime ) {
	foreach ( BulletSpawner*, it, mSpawners ) {
		(*it)->Update( deltaTime );
	}
}
void GameScene::BatchSprites() {
	mSpriteBatcher->Clear();
	foreach ( BulletSpawner*, it, mSpawners ) {
		(*it)->Render( mSpriteBatcher );
	}
	mShip->Render( mSpriteBatcher );
}

void GameScene::CheckCollision() {
	foreach ( BulletSpawner*, it, mSpawners ) {
		if ( (*it)->CheckCollision( mShip ) == true ) {
			mShip->OnDead();
			return;
		}
	}
}