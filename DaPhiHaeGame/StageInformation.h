#pragma once

#include <vector>
class BulletManager;

class StageInformation
{
private:
	struct SpawnerData {
		float startTime;
		float lifeTime;
		float interval;
		Vector2 initialSpeed;
	};
public:
	StageInformation( BulletManager* bulletManager );
	~StageInformation();

	void Update( float deltaTime );
	void Retry();

private:
	void NewSpawner( const SpawnerData& spawnerData );

private:
	std::vector<SpawnerData> mSpawnerDatas;
	
	int		mNextSpawnerIndex;
	float	mStageElapsedSeconds;

	BulletManager* const mBulletManager;

};