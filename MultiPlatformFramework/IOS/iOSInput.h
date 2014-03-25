//
//  iOSInput.h
//  Project-iOS
//
//  Created by Robin Kang on 2014. 3. 24..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#ifndef __Project_iOS__iOSInput__
#define __Project_iOS__iOSInput__

#include "Common/CommonInput.h"


class CIOSInput : public CommonInput
{
public:
    CIOSInput();
    virtual ~CIOSInput();
    
    float GetAccelX() const;
    float GetAccelY() const;
    float GetAccelZ() const;
};

#endif /* defined(__Project_iOS__iOSInput__) */
