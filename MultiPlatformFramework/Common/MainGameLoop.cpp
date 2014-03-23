
#include "stdafx.h"

#include "Interfaces/IGame.h"
#include "Interfaces/IGameLoopListener.h"

#include "MainGameLoop.h"
#include "logger.h"
#include "Timer.h"
#include "CommonHeaders.h"

#define LOG_TAG "MainGameLoop"

MainGameLoop::MainGameLoop( IGame* gameInstance, IGameLoopListener* listener, Timer* tickTimer )
    : mGameInstance( gameInstance )
	, mTickTimer( tickTimer )
	, mListener( listener )
{
	assert( gameInstance != NULL );
	assert( tickTimer != NULL );
	assert( listener != NULL );

	LOG_INFO("GameLoop instance created");
    pthread_mutex_init(&_mutex, 0);
    return;
}

MainGameLoop::~MainGameLoop()
{
	LOG_INFO("GameLoop instance destroyed");
    pthread_mutex_destroy(&_mutex);

	mGameInstance = NULL;
	mTickTimer = NULL;
	mListener = NULL;

    return;
}

void MainGameLoop::Start()
{
	LOG_INFO("Creating GameLoop thread");
	mMessageQueue.push( ThreadMessage( MSG_RESUME, NULL ) );
    pthread_create(&_threadId, 0, threadStartCallback, this);
    return;
}

void MainGameLoop::Stop()
{
	LOG_INFO("Stopping GameLoop thread");
    // send message to render thread to stop rendering
    pthread_mutex_lock(&_mutex);
    mMessageQueue.push( ThreadMessage( MSG_RENDER_LOOP_EXIT, NULL ) );
    pthread_mutex_unlock(&_mutex);

    pthread_join(_threadId, 0);
    return;
}

void MainGameLoop::PushMessage( GameThreadMessage message, void* args ) {
	pthread_mutex_lock( &_mutex );
	mMessageQueue.push( ThreadMessage( message, args ) );
//	LOG_INFO( "PushMessage %d", message);
    pthread_mutex_unlock( &_mutex );
}

void MainGameLoop::MainLoop()
{
    bool renderingEnabled = true;

    mTickTimer->Tick();
    while (renderingEnabled) {
        pthread_mutex_lock(&_mutex);

        // process incoming messages
		if ( mMessageQueue.empty() == false ) {
			ThreadMessage msg = mMessageQueue.front();

//	    	LOG_INFO("ProcessMessage %d", msg.messageType);
			switch ( msg.messageType ) {
			case MSG_WINDOW_SET:
				mListener->OnWindowChanged( msg.args );
				mGameInstance->Resume();
				break;

			case MSG_TOUCH_EVENT:
				mListener->OnTouchEvent( msg.args );
				break;

			case MSG_RESUME:
				mListener->OnResume();
				mGameInstance->Resume();
				break;

			case MSG_RENDER_LOOP_EXIT:
				// when stop() has called
				renderingEnabled = false;
				mGameInstance->Pause();
				mListener->OnPause();
				break;
                    
            default:
                break;
			}

			mMessageQueue.pop();
		}
		else {
			float deltaTime = mTickTimer->Tick();
			// trash too long frame
			if ( deltaTime < 1.0f ) {
				mGameInstance->Update( deltaTime );
				mGameInstance->Render();
				mListener->OnPresent();
			}
		}
        
        pthread_mutex_unlock(&_mutex);

		mListener->OnTakeABreak();
    }
    return;
}

void* MainGameLoop::threadStartCallback(void *myself)
{
	MainGameLoop *loop = (MainGameLoop*)myself;

    loop->MainLoop();
    pthread_exit(0);
    
    return 0;
}
