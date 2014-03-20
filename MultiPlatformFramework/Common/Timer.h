#ifndef Timer_H_
#define Timer_H_

class Timer
{
public:
	Timer();
	virtual ~Timer();

	float Tick();
	void CheckFps(float deltaTime);

protected:
	virtual float GetCurrentSecond() const = 0;

private:
	float mCurrentTickTime;
	float mLastTickTime;

	int fps;
	float fpsCheckTime;
};

#endif	// Timer_H_
