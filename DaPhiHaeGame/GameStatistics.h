#pragma once

#include "TSingleton.hpp"

#define gGameStatistics GameStatistics::getInstancePtr()

class GameStatistics : public TSingleton<GameStatistics>
{
public:
	GameStatistics();
	~GameStatistics();

	void Save() const;
	void Load();
	void InitScore();

	void GameStart();
	void GameFinished();
	
	void CountElapsedTime( float deltaTime );
	void LevelUp();

	int GetCurrentScore() const;
	int GetHighScore( int rank ) const;
	int GetCurrentLevel() const;

private:
	const static int cNumScoresToSave = 3;
	const static char* const cSaveFileName;

private:
	int mCurrentScore;
	int mHighScore[cNumScoresToSave];

	float mElapsedTime;
	int mCurrentLevel;
};

