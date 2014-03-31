#pragma once

#include "Interfaces/IGame.h"
#include "Asset.h"

class IPlatform;

class DaPhiHae : public IGame {
public:
	DaPhiHae( IPlatform* platformInstance );
	~DaPhiHae();

	void Resume();
	void Pause();
	void Update( float deltaTime );
	void Render() const;

private:
	IPlatform* 	mPlatform;
	Asset mAsset;

	IGame* mCurrentScene;
};

