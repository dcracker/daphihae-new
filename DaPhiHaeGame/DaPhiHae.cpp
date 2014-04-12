#include "stdafx.h"
#include "DaPhiHae.h"

#include "Interfaces/IPlatform.h"
#include "GameScene.h"

DaPhiHae::DaPhiHae( IPlatform* platformInstance )
	: mPlatform( platformInstance )
	, mAsset()
	, mCurrentScene( NULL )
{
	mCurrentScene = new GameScene( platformInstance );
}


DaPhiHae::~DaPhiHae()
{
	SAFE_DELETE( mCurrentScene );
}

void DaPhiHae::Resume() {
	mAsset.Resume( mPlatform->GetFileIO() );
	mCurrentScene->Resume();
}

void DaPhiHae::Pause() {
	mCurrentScene->Pause();
}

void DaPhiHae::Update( float deltaTime ) {
	mCurrentScene->Update( deltaTime );
}

void DaPhiHae::Render() const {
	mCurrentScene->Render();
}
