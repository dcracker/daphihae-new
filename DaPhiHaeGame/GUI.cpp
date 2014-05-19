#include "stdafx.h"
#include "GUI.h"
#include "Asset.h"
#include "BitmapFont.h"
#include "GameStatistics.h"
#include "StageInformation.h"

GUI::GUI( int screenWidth, int screenHeight )
	: cHighScorePosition( 10, screenHeight - 10 )
	, cCurrentScorePosition( 10, 10 )
	, cLevelNumberPosition( screenWidth - 50, 10 )
{
}


GUI::~GUI()
{
}

void GUI::DrawGUI( SpriteBatcher* batcher ) const {
	const int bufferSize = 10;
	char buf[bufferSize];
	_itoa_s( gGameStatistics->GetHighScore( 1 ), buf, bufferSize, 10 );
	gAsset->font->DrawTexts( buf, cHighScorePosition, batcher );
	_itoa_s( gGameStatistics->GetCurrentScore(), buf, bufferSize, 10 );
	gAsset->font->DrawTexts( buf, cCurrentScorePosition, batcher );
	_itoa_s( gGameStatistics->GetCurrentLevel(), buf, bufferSize, 10 );
	gAsset->font->DrawTexts( buf, cLevelNumberPosition, batcher );
}