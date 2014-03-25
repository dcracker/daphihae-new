//
//  iOSTimer.mm
//  Project-iOS
//
//  Created by Robin Kang on 2014. 3. 24..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#include "iOSTimer.h"


CIOSTimer::CIOSTimer()
{
    mach_timebase_info( &m_timeInfo );
    Tick();
}

CIOSTimer::~CIOSTimer()
{
}


float CIOSTimer::GetCurrentSecond() const
{
    float gcs = ((float)mach_absolute_time() * (float)m_timeInfo.numer) / ((float)m_timeInfo.denom * 1000000000.0f);
//    NSLog( @"gcs: %f", gcs );
    return gcs;
}

