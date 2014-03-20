#pragma once
#include "../Common/Timer.h"

class WindowsTimer : public Timer
{
public:
	WindowsTimer();
	~WindowsTimer();

	float GetCurrentSecond() const;
};

