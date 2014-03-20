#pragma once
#include "../Interfaces/IPlatform.h"
#include "../Interfaces/IGameLoopListener.h"

class WindowsGraphics;
class WindowsInput;
class WindowsFileIO;

class WindowsPlatform : public IPlatform, public IGameLoopListener
{
public:
	WindowsPlatform( WindowsGraphics* graphics );
	~WindowsPlatform();

// IPlatform
public:
		  IInput*		GetInput() const;
	const IFileIO*		GetFileIO() const;
	const IGraphics*	GetGraphics() const;
	const IAudio*		GetAudio() const { return NULL; };

private:
	WindowsGraphics*	mGraphics;
	WindowsInput*		mInput;
	WindowsFileIO*		mFileIO;

// IGameLoopListener
private:
	void OnWindowChanged( void* args );
	void OnTouchEvent( void* args );

	void OnResume();
	void OnPause();
	void OnPresent() const;
	void OnTakeABreak() const;
};

