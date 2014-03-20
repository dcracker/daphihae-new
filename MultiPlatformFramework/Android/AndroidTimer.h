#ifndef AndroidTimer_H_
#define AndroidTimer_H_

#include "../Common/Timer.h"

class AndroidTimer : public Timer
{
public:
	AndroidTimer();
	~AndroidTimer();
private:
	float GetCurrentSecond() const;
};

#endif	// AndroidTimer_H_
