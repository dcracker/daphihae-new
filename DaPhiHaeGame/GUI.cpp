#include "stdafx.h"
#include "GUI.h"
#include "Asset.h"
#include "BitmapFont.h"
#include "GameStatistics.h"
#include <string>

GUI::GUI( int screenWidth, int screenHeight )
	: cHighScorePosition( 5, screenHeight - 20 )
	, cCurrentScorePosition( 5, 5 )
	, cLevelNumberPosition( screenWidth - 50, 5 )
	, cGameOverPosition( screenWidth * 0.5f - 22.5, screenHeight * 0.5f + 40 )
	, cRankingPosition( cGameOverPosition.x - 10, cGameOverPosition.y - 30 )
{
}


GUI::~GUI()
{
}

void GUI::DrawInGameGUI( SpriteBatcher* batcher ) const {
	DrawTexts( "High Score : ", gGameStatistics->GetHighScore( 1 ), cHighScorePosition, batcher );
	DrawTexts( "Score : ", gGameStatistics->GetCurrentScore(), cCurrentScorePosition, batcher );
	DrawTexts( "Lv : ", gGameStatistics->GetCurrentLevel(), cLevelNumberPosition, batcher );
}

void GUI::DrawGameOverScreen( SpriteBatcher* batcher ) const {
	DrawTexts( "Game Over", cGameOverPosition, batcher );

	Vector2 currentRankingPosition = cRankingPosition;
	DrawTexts( "1st : ", gGameStatistics->GetHighScore( 1 ), currentRankingPosition, batcher );

	currentRankingPosition.y -= 15;
	DrawTexts( "2nd : ", gGameStatistics->GetHighScore( 2 ), currentRankingPosition, batcher );

	currentRankingPosition.y -= 15;
	DrawTexts( "3rd : ", gGameStatistics->GetHighScore( 3 ), currentRankingPosition, batcher );
}

void GUI::DrawTexts( const char* texts, const Vector2& position, SpriteBatcher* batcher ) {
	gAsset->boldFont->DrawTexts( texts, position, batcher );
}

void GUI::DrawTexts( const char* texts, int number, const Vector2& position, SpriteBatcher* batcher ) {
	const int bufSize = 20;
	char buffer[bufSize];

	MakeString( texts, number, buffer, bufSize );
	DrawTexts( buffer, position, batcher );
}

void GUI::MakeString( const char* text, int number, char* out_buffer, int bufSize ) {
	sprintf_s( out_buffer, bufSize, "%s%d", text, number );
}