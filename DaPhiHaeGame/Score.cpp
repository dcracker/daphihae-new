#include "stdafx.h"
#include "Score.h"

Score::Score()
	: mCurrentScore( 0 )
{
}


Score::~Score()
{
}

void Score::AddScore( int score ) {
	mCurrentScore += score;
}

void Score::GameStart() {
	mCurrentScore = 0;
}

void Score::GameFinished() {
	int newScore = mCurrentScore;
	for ( int i=0; i < cNumScoresToSave; ++i ) {
		if ( mHighScores[i] < newScore ) {
			int swapBuffer = mHighScores[i];
			mHighScores[i] = newScore;
			newScore = swapBuffer;
		}
	}
}

int Score::GetCurrentScore() const {
	return mCurrentScore;
}

int Score::GetHighScore( int rank ) const {
	return mHighScores[rank - 1];
}