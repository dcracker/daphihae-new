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
	sprintf_s( buf, bufferSize, "%d", gGameStatistics->GetHighScore( 1 ) );
	guiText.append( buf );
	gAsset->font->DrawTexts( guiText.c_str(), cHighScorePosition, batcher );

	guiText = "Score : ";
	sprintf_s( buf, bufferSize, "%d", gGameStatistics->GetCurrentScore() );
	guiText.append( buf );
	gAsset->font->DrawTexts( guiText.c_str(), cCurrentScorePosition, batcher );

	guiText = "Lv : ";
	sprintf_s( buf, bufferSize, "%d", gGameStatistics->GetCurrentLevel() );
	guiText.append( buf );
	gAsset->font->DrawTexts( guiText.c_str(), cLevelNumberPosition, batcher );
}
