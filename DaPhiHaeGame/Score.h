#pragma once

class Score
{
public:
	Score();
	~Score();

	void Save() const {}
	void Load() {
		mHighScores[0] = 1000;
		mHighScores[1] = 500;
		mHighScores[2] = 100;
	}

	void AddScore( int score );
	void GameStart();
	void GameFinished();

	int GetCurrentScore() const;
	int GetHighScore( int rank ) const;

private:
	int mCurrentScore;

	const static int cNumScoresToSave = 3;
	int mHighScores[cNumScoresToSave];
};

