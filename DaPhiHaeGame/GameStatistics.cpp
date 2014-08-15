#include "stdafx.h"
#include "GameStatistics.h"
#include "Interfaces/IPlatform.h"
#include "Interfaces/IFileReader.h"
#include "Interfaces/IFileWriter.h"
#include "logger.h"

#define LOG_TAG "GameStatistics"

const char* const GameStatistics::cSaveFileName = "score.dph";

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

void GameStatistics::Save() const {
	IFileWriter* saveFile = IPlatform::getInstancePtr()->GetFileIO()->WriteData( cSaveFileName );
	if ( saveFile == NULL ) {
		LOG_ERROR( "save file create failed." );
		return;
	}
	saveFile->WriteByte( mHighScore, sizeof(mHighScore[0]) * 3 );
	saveFile->Close();
}

void GameStatistics::Load() {
	IFileReader* saveFile = IPlatform::getInstancePtr()->GetFileIO()->ReadData( cSaveFileName );
	if ( saveFile == NULL ) {
		InitScore();
	}
	else {
		saveFile->ReadByte( mHighScore, sizeof(mHighScore[0]) * 3 );
		saveFile->Close();
	}
}

void GameStatistics::InitScore() {
	mHighScore[0] = 100;
	mHighScore[1] = 50;
	mHighScore[2] = 10;
}
