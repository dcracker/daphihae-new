#include "stdafx.h"
#include "WindowsTimer.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

WindowsTimer::WindowsTimer()
{
	Tick();
}


WindowsTimer::~WindowsTimer()
{
}

float WindowsTimer::GetCurrentSecond() const {
	return (float)timeGetTime() / 1000.f;
}