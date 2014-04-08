//
// Copyright 2011 Tero Saarni
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef MainGameLoop_H
#define MainGameLoop_H

#include <pthread.h>
#include <queue>

class IGame;
class Timer;
class IGameLoopListener;

class MainGameLoop {
public:
    enum GameThreadMessage {
        MSG_NONE				= 0,
        MSG_RESUME				= 1,
        MSG_RENDER_LOOP_EXIT	= 2,
        MSG_WINDOW_SET			= 3,
    };

public:
	MainGameLoop( IGame* gameInstance, IGameLoopListener* listener, Timer* tickTimer );
    ~MainGameLoop();

    // Following methods can be called from any thread.
    // They send message to render thread which executes required actions.
    void Start();
    void Stop();

	void PushMessage( GameThreadMessage message, void* args );
    
private:
    // RenderLoop is called in a rendering thread started in start() method
    // It creates rendering context and renders scene until stop() is called
    void MainLoop();

    // Helper method for starting the thread 
    static void* threadStartCallback(void *myself);

private:
	struct ThreadMessage {
		GameThreadMessage messageType;
		void*				args;
		ThreadMessage( GameThreadMessage _msg, void* _args )
			: messageType( _msg )
			, args( _args )
		{}
	};
	std::queue<ThreadMessage>	mMessageQueue;
    
private:
    pthread_t _threadId;
    pthread_mutex_t _mutex;

private:
    IGame* 				mGameInstance;
	Timer*				mTickTimer;
	IGameLoopListener*	mListener;
};

#endif // MainGameLoop_H
