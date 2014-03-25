//
//  iOSTimer.h
//  Project-iOS
//
//  Created by Robin Kang on 2014. 3. 24..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#ifndef __Project_iOS__iOSTimer__
#define __Project_iOS__iOSTimer__

#include <mach/mach_time.h>
#include "Common/Timer.h"


class CIOSTimer : public Timer
{
private:
    mach_timebase_info_data_t m_timeInfo;
    
public:
    CIOSTimer();
    virtual ~CIOSTimer();
    
    float GetCurrentSecond() const;
};


#endif /* defined(__Project_iOS__iOSTimer__) */
