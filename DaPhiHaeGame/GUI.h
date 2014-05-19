#pragma once

class SpriteBatcher;
class GameStatistics;
class StageInformation;

class GUI
{
public:
	GUI( int screenWidth, int screenHeight );
	~GUI();

	void DrawGUI( SpriteBatcher* batcher ) const;

private:
	const Vector2 cHighScorePosition;
	const Vector2 cCurrentScorePosition;
	const Vector2 cLevelNumberPosition;
};

