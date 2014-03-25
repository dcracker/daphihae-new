//
//  iOSPlatform.h
//  MultiPlatformTest_iOS
//
//  Created by Robin Kang on 2014. 1. 27..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#ifndef MultiPlatformTest_iOS_iOSPlatform_h
#define MultiPlatformTest_iOS_iOSPlatform_h


#include "Interfaces/IPlatform.h"
#include "Interfaces/IGameLoopListener.h"
#include "iOSGraphics.h"
#include "iOSInput.h"
#include "iOSFileIO.h"


class CIOSPlatform : public IPlatform, public IGameLoopListener
{
protected:
    CIOSGraphics* m_Graphics;
    CIOSInput* m_Input;
    CIOSFileIO* m_FileIO;
    
public:
	CIOSPlatform( CIOSGraphics* graphics );
    virtual ~CIOSPlatform();
    
	IInput*		GetInput() const;
	const IFileIO*	GetFileIO() const;
	const IGraphics*	GetGraphics() const;
	const IAudio*		GetAudio() const;
    
private:
    void OnWindowChanged( void* args );
    void OnTouchEvent( void* args );
    void OnResume();
    void OnPause();
    void OnPresent() const;
    void OnTakeABreak() const;
};


#endif
