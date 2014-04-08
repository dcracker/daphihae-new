#ifndef IGameLoopListener_H_
#define IGameLoopListener_H_

class IGameLoopListener {
public:
	virtual ~IGameLoopListener() {}

	// when receieve MSG_WINDOW_SET
	virtual void OnWindowChanged( void* args ) = 0;

	// when thread start
	virtual void OnResume() = 0;
	// when thread stop
	virtual void OnPause() = 0;

	virtual void OnPresent() const = 0;
	virtual void OnTakeABreak() const = 0;
};

#endif	// IGameLoopListener_H_
