
#include "stdafx.h"

#include "Timer.h"
#include "logger.h"

#define LOG_TAG "FPS"

Timer::Timer() 
	: fpsCheckTime( 1 )
	, fps( 0 )
	, mCurrentTickTime( 0 )
	, mLastTickTime( 0 )
{}

Timer::~Timer() {}

float Timer::Tick() {
	mCurrentTickTime = GetCurrentSecond();
	float deltaTime = mCurrentTickTime - mLastTickTime;
	mLastTickTime = mCurrentTickTime;

	CheckFps( deltaTime );
	return deltaTime;
}

void Timer::CheckFps(float deltaTime) {
	if ( deltaTime > 1 ) return;

	++fps;
	fpsCheckTime -= deltaTime;
	if ( fpsCheckTime <= 0 ) {
		LOG_INFO( "FPS : %d", fps );
		fpsCheckTime += 1;
		fps = 0;
	}
}
