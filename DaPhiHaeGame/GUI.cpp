#include "stdafx.h"
#include "GUI.h"
#include "Asset.h"
#include "BitmapFont.h"
#include "GameStatistics.h"
#include "StageInformation.h"
#include <string>

GUI::GUI( int screenWidth, int screenHeight )
	: cHighScorePosition( 5, screenHeight - 20 )
	, cCurrentScorePosition( 5, 5 )
	, cLevelNumberPosition( screenWidth - 50, 5 )
{
}


GUI::~GUI()
{
}

void GUI::DrawGUI( SpriteBatcher* batcher ) const {
	const int bufferSize = 10;
	char buf[bufferSize];
	std::string guiText;
	guiText = "High Score : ";
	_itoa_s( gGameStatistics->GetHighScore( 1 ), buf, bufferSize, 10 );
	guiText.append( buf );
	gAsset->font->DrawTexts( guiText.c_str(), cHighScorePosition, batcher );

	guiText = "Score : ";
	_itoa_s( gGameStatistics->GetCurrentScore(), buf, bufferSize, 10 );
	guiText.append( buf );
	gAsset->font->DrawTexts( guiText.c_str(), cCurrentScorePosition, batcher );

	guiText = "Lv : ";
	_itoa_s( gGameStatistics->GetCurrentLevel(), buf, bufferSize, 10 );
	guiText.append( buf );
	gAsset->font->DrawTexts( guiText.c_str(), cLevelNumberPosition, batcher );
}