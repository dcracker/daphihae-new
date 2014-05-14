#pragma once

class SpriteBatcher;
class Score;
class StageInformation;

class GUI
{
public:
	GUI( int screenWidth, int screenHeight );
	~GUI();

	void DrawGUI( int currentScore, int highestScore, int level, SpriteBatcher* batcher ) const;

private:
	const Vector2 cHighScorePosition;
	const Vector2 cCurrentScorePosition;
	const Vector2 cLevelNumberPosition;
};

