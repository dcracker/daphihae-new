#include "stdafx.h"
#include "AndroidTimer.h"

#include <time.h>

AndroidTimer::AndroidTimer() {
	Tick();
}

AndroidTimer::~AndroidTimer() {

}

float AndroidTimer::GetCurrentSecond() const {
	timespec timeNow;
	clock_gettime( CLOCK_MONOTONIC, &timeNow );
	return (timeNow.tv_sec * 1000000000ull + timeNow.tv_nsec) * 0.000000001f;
}