#include "stdafx.h"
#include "StageInformation.h"
#include "BulletManager.h"
#include "GameStatistics.h"

StageInformation::StageInformation()
	: mNextSpawnerIndex( 0 )
	, mStageElapsedSeconds( 0 )
{
	// level 1
	float time = 0;
	float life = 5;
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -240 ) } );

	// level 2
	time += life;
	life = 10;
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -240 ) } );
	mSpawnerDatas.push_back( { time, life, 0.6f, Vector2( 0, -360 ) } );

	// level 3
	time += life;
	life = 13;
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -180 ) } );
	mSpawnerDatas.push_back( { time, life, 0.4f, Vector2( 0, -360 ) } );

	// level 4
	time += life;
	life = 17;
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -240 ) } );
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -360 ) } );
	mSpawnerDatas.push_back( { time, life, 0.6f, Vector2( 0, -180 ) } );

	// level 5
	time += life;
	life = 20;
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -180 ) } );
	mSpawnerDatas.push_back( { time, life, 0.4f, Vector2( 0, -240 ) } );
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -360 ) } );

	// level 6
	time += life;
	life = 24;
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -240 ) } );
	mSpawnerDatas.push_back( { time, life, 0.4f, Vector2( 0, -180 ) } );
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -360 ) } );
	mSpawnerDatas.push_back( { time, life, 0.8f, Vector2( 0, -600 ) } );
	
	// level 7
	time += life;
	life = 28;
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -180 ) } );
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -240 ) } );
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -360 ) } );
	mSpawnerDatas.push_back( { time, life, 0.6f, Vector2( 0, -600 ) } );
	
	// level 8
	time += life;
	life = 36;
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -240 ) } );
	mSpawnerDatas.push_back( { time, life, 0.5f, Vector2( 0, -060 ) } );
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -360 ) } );
	mSpawnerDatas.push_back( { time, life, 0.6f, Vector2( 0, -600 ) } );
	mSpawnerDatas.push_back( { time, life, 1.0f, Vector2( 0, -900 ) } );
	
	// level 9
	time += life;
	life = FLT_MAX;
	mSpawnerDatas.push_back( { time, life, 0.5f, Vector2( 0, -060 ) } );
	mSpawnerDatas.push_back( { time, life, 0.2f, Vector2( 0, -240 ) } );
	mSpawnerDatas.push_back( { time, life, 0.1f, Vector2( 0, -360 ) } );
	mSpawnerDatas.push_back( { time, life, 0.7f, Vector2( 0, -600 ) } );
	mSpawnerDatas.push_back( { time, life, 0.6f, Vector2( 0, -900 ) } );
}


StageInformation::~StageInformation()
{
}

void StageInformation::Update( float deltaTime ) {

	mStageElapsedSeconds += deltaTime;
	unsigned int i;
	for ( i = mNextSpawnerIndex; i < mSpawnerDatas.size() && mSpawnerDatas[i].startTime <= mStageElapsedSeconds; ++i ) {
		NewSpawner( mSpawnerDatas[i] );
	}

	if ( mNextSpawnerIndex != i ) {
		gGameStatistics->LevelUp();
		mNextSpawnerIndex = i;
	}
}

void StageInformation::Retry() {
	mStageElapsedSeconds = 0;
	mNextSpawnerIndex = 0;
	Update( 0 );
}

void StageInformation::NewSpawner( const SpawnerData& spawnerData ) {
	BulletManager::getInstancePtr()->AddSpawner( spawnerData.interval, spawnerData.initialSpeed, spawnerData.lifeTime );
}

int StageInformation::GetCurrentLevel() const {
	// TODO : This value cannot use to level number
	return mNextSpawnerIndex;
}