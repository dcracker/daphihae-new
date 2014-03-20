//
//  iOSPlatform.h
//  MultiPlatformTest_iOS
//
//  Created by Robin Kang on 2014. 1. 27..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#ifndef MultiPlatformTest_iOS_iOSPlatform_h
#define MultiPlatformTest_iOS_iOSPlatform_h

#include "IPlatform.h"
#include "iOSGraphics.h"

class CIOSPlatform : public IPlatform
{
public:
	CIOSPlatform( UIView *viewRoot );
	~CIOSPlatform();
    
	IInput*		GetInput() const { return NULL; };
	IFileIO*	GetFileIO() const { return NULL; };
	IGraphics*	GetGraphics() const { return m_Graphics; };
	IAudio*		GetAudio() const { return NULL; };

private:
	CIOSGraphics* m_Graphics;
};


#endif
