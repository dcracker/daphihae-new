//
//  iOSGraphics.h
//  MultiPlatformTest_iOS
//
//  Created by Robin Kang on 2014. 1. 26..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#ifndef MultiPlatformTest_iOS_iOSGraphics_h
#define MultiPlatformTest_iOS_iOSGraphics_h


#include "Interfaces/IGraphics.h"

class CIOSGraphics : public IGraphics
{
public:
    CIOSGraphics();
    virtual ~CIOSGraphics();
    
	virtual int GetWidth() const;
	virtual int GetHeight() const;
    virtual float GetAspectRatio() const;
};


#endif

