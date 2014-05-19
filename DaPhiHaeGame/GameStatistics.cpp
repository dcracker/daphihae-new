#include "stdafx.h"
#include "GameStatistics.h"

GameStatistics::GameStatistics()
	: mCurrentScore( 0 )
	, mElapsedTime( 0 )
	, mCurrentLevel( 0 )
{
}


GameStatistics::~GameStatistics()
{
}

void GameStatistics::GameStart() {
	mCurrentScore = 0;
	mElapsedTime = 0;
	mCurrentLevel = 1;
}

void GameStatistics::GameFinished() {
	int newGameStatistics = mCurrentScore;
	for ( int i=0; i < cNumScoresToSave; ++i ) {
		if ( mHighScore[i] < newGameStatistics ) {
			int swapBuffer = mHighScore[i];
			mHighScore[i] = newGameStatistics;
			newGameStatistics = swapBuffer;
		}
	}
}

void GameStatistics::CountElapsedTime( float deltaTime ) {
	mElapsedTime += deltaTime;
	mCurrentScore = static_cast<int>(mElapsedTime);
}

void GameStatistics::LevelUp() {
	++mCurrentLevel;
}

int GameStatistics::GetCurrentScore() const {
	return mCurrentScore;
}

int GameStatistics::GetHighScore( int rank ) const {
	return mHighScore[rank - 1];
}

int GameStatistics::GetCurrentLevel() const {
	return mCurrentLevel;
}