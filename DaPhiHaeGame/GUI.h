#pragma once

class SpriteBatcher;
class GameStatistics;
class StageInformation;

class GUI
{
public:
	GUI( int screenWidth, int screenHeight );
	~GUI();

	void DrawTitleScreen( SpriteBatcher* batcher ) const;
	void DrawInGameGUI( SpriteBatcher* batcher ) const;
	void DrawGameOverScreen( SpriteBatcher* batcher ) const;

private:
	static void DrawTexts( const char* texts, const Vector2& position, SpriteBatcher* batcher );
	static void DrawTexts( const char* texts, int number, const Vector2& position, SpriteBatcher* batcher );
	static void MakeString( const char* text, int number, char* out_buffer, int bufSize );

private:
	const Vector2 cHighScorePosition;
	const Vector2 cCurrentScorePosition;
	const Vector2 cLevelNumberPosition;

	const Vector2 cGameOverPosition;
	const Vector2 cRankingPosition;

	const Vector2 cTitlePosition;
	const Vector2 cTitleSize;
	const Vector2 cStartMessagePosition;
};

