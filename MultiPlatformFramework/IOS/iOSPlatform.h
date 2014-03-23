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
#include "iOSGraphics.h"

class CIOSPlatform : public IPlatform
{
protected:
    CIOSGraphics* m_Graphics;
    
public:
	CIOSPlatform();
	virtual ~CIOSPlatform();
    
	IInput*		GetInput() const;
	const IFileIO*	GetFileIO() const;
	const IGraphics*	GetGraphics() const;
	const IAudio*		GetAudio() const { return NULL; };

protected:
};


#endif
