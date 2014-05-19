#include "stdafx.h"
#include "GameScene.h"

#include "Interfaces/IPlatform.h"
#include "Asset.h"
#include "SpriteBatcher.h"
#include "GUI.h"
#include "Camera2D.h"
#include "BitmapFont.h"

#include "Ship.h"
#include "BulletManager.h"
#include "StageInformation.h"
#include "GameStatistics.h"
#include "Util.h"

GameScene::GameScene( IPlatform* platform )
	: mPlatform( platform )
	, mMainCam( new Camera2D( 0, static_cast<float>(cWorldWidth), 0, static_cast<float>(cWorldHeight) ) )
	, mSpriteBatcher( new SpriteBatcher( gAsset->mainAtlas ) )
	, mShip( new Ship() )
	, mStageInfo( NULL )
	, mBulletManager( new BulletManager() )
	, mGUI( new GUI( cWorldWidth, cWorldHeight ) )
	, mGameStatistics( new GameStatistics() )
{
	mStageInfo = new StageInformation( mBulletManager );

	RestartGame();
	mGameStatistics->Load();
}

GameScene::~GameScene()
{
	SAFE_DELETE( mMainCam );
	SAFE_DELETE( mSpriteBatcher );
	SAFE_DELETE( mGUI );
	SAFE_DELETE( mShip );
	SAFE_DELETE( mBulletManager );
	SAFE_DELETE( mStageInfo );
	SAFE_DELETE( mGameStatistics );
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
	mGameStatistics->Save();
}

void GameScene::Update( float deltaTime ) {
	ProcessTouchInput();
	mBulletManager->Update( deltaTime );
	mStageInfo->Update( deltaTime );
	mShip->Update( deltaTime );

	if ( IsGameRunning() ) {
		CheckCollision();
		gGameStatistics->CountElapsedTime( deltaTime );
	}

	BatchSprites();
}

void GameScene::Render() const {
    glClear( GL_COLOR_BUFFER_BIT );
	mMainCam->Bind();
	mSpriteBatcher->Render();
}

bool GameScene::IsGameRunning() const {
	return mShip->IsAlive() == true;
}

void GameScene::RestartGame() {
	mShip->Start( static_cast<float>(cWorldWidth * 0.5f), 100.f );
	mBulletManager->Reset();
	mStageInfo->Retry();	// need to call after mBulletManager::Reset();
	mGameStatistics->GameStart();
}

void GameScene::ProcessTouchInput() {
	if ( IsGameRunning() ) {
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

void GameScene::BatchSprites() {
	mSpriteBatcher->Clear();
	mBulletManager->Render( mSpriteBatcher );
	mShip->Render( mSpriteBatcher );
	mGUI->DrawGUI( mSpriteBatcher );
}

void GameScene::CheckCollision() {
	if ( mBulletManager->CheckCollision( mShip ) == true ) {
		mShip->OnDead();
		mGameStatistics->GameFinished();
	}
}