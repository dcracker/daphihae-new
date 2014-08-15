#ifndef AndroidPlatform_H_
#define AndroidPlatform_H_

#include <jni.h>
#include "../Interfaces/IPlatform.h"
#include "../Interfaces/IGameLoopListener.h"

class AndroidGraphics;
class AndroidInput;
class AndroidFileIO;
class AndroidAudio;
class CommonTouchMessageHandler;

class AndroidPlatform : public IPlatform, public IGameLoopListener {
public:
	AndroidPlatform( JNIEnv* env, jobject assetManager, const char* dataRoot, const CommonTouchMessageHandler* touchHandler );
	~AndroidPlatform();

		  IInput*		GetInput() 		const;
	const IFileIO*		GetFileIO() 	const;
	const IGraphics*	GetGraphics() 	const;
	const IAudio*		GetAudio() 		const { return NULL; };

private:
	JavaVM*				mJavaVM;
	JNIEnv*				mJniEnv;

	AndroidGraphics* 	mGraphics;
	AndroidInput*		mInput;
	AndroidFileIO*		mFileIO;

// IGameLoopListener
private:
	void OnWindowChanged( void* args );
	void OnTouchEvent( void* args );

	void OnResume();
	void OnPause();
	void OnPresent() const;
	void OnTakeABreak() const;
};

#endif	// AndroidPlatform_H_
