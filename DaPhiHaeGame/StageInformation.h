#pragma once

#include <vector>

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
	StageInformation();
	~StageInformation();

	void Update( float deltaTime );
	void Retry();

private:
	static void NewSpawner( const SpawnerData& spawnerData );

private:
	std::vector<SpawnerData> mSpawnerDatas;
	
	int		mNextSpawnerIndex;
	float	mStageElapsedSeconds;
};