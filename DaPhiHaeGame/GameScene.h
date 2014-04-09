#pragma once
#include "Interfaces/IGame.h"
#include <vector>

class IPlatform;
class Camera2D;
class SpriteBatcher;
class Sprite;

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
	void ProcessTouchInput();
	void BatchSprites();
	void UpdateBullets( float deltaTime );
	void UpdateShip( float deltaTime );
	void CheckCollision();

private:
	static const int cWorldWidth = 320;
	static const int cWorldHeight = 480;
	
	// process only 2 fingers.
	static const int cMaxNumFingers = 2;

private:
	IPlatform* mPlatform;

	Camera2D* mMainCam;
	SpriteBatcher* mSpriteBatcher;

	std::vector<Sprite*> mBullets;
	Sprite* mShip;
	float mShipSpeed;
};

