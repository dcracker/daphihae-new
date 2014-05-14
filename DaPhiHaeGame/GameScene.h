#pragma once
#include "Interfaces/IGame.h"
#include <vector>

class IPlatform;
class Camera2D;
class SpriteBatcher;
class GUI;
class Sprite;
class Ship;
class BulletManager;
class StageInformation;
class Score;

class GameScene : public IGame
{
public:
	GameScene( IPlatform* platform );
	~GameScene();

	void Resume();
	void Pause();
	void Update( float deltaTime );
	void Render() const;

private:
	void RestartGame();
	void ProcessTouchInput();
	void ProcessInputForMove();
	void ProcessInputForRestart();
	void BatchSprites();
	void UpdateBullets( float deltaTime );
	void CheckCollision();

public:
	static const int cWorldWidth = 320;
	static const int cWorldHeight = 480;
private:
	// process only 2 fingers.
	static const int cMaxNumFingers = 2;

private:
	IPlatform* mPlatform;

	Camera2D*		mMainCam;
	SpriteBatcher*	mSpriteBatcher;
	GUI*			mGUI;

	Ship*			mShip;
	BulletManager*	mBulletManager;
	StageInformation*	mStageInfo;
	Score*			mScore;

	float			mScoreTimer;
};

