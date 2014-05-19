#pragma once

#include "TSingleton.hpp"

#define gGameStatistics GameStatistics::getInstancePtr()

class GameStatistics : public TSingleton<GameStatistics>
{
public:
	GameStatistics();
	~GameStatistics();

	void Save() const {}
	void Load() {
		mHighScore[0] = 1000;
		mHighScore[1] = 500;
		mHighScore[2] = 100;
	}

	void GameStart();
	void GameFinished();
	
	void CountElapsedTime( float deltaTime );
	void LevelUp();

	int GetCurrentScore() const;
	int GetHighScore( int rank ) const;
	int GetCurrentLevel() const;

private:
	int mCurrentScore;

	const static int cNumScoresToSave = 3;
	int mHighScore[cNumScoresToSave];

	float mElapsedTime;
	int mCurrentLevel;
};

