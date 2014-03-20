//
//  iOSGraphics.h
//  MultiPlatformTest_iOS
//
//  Created by Robin Kang on 2014. 1. 26..
//  Copyright (c) 2014년 KangRobin. All rights reserved.
//

#ifndef MultiPlatformTest_iOS_iOSGraphics_h
#define MultiPlatformTest_iOS_iOSGraphics_h


#include "IGraphics.h"

class CIOSGraphics : public IGraphics
{
public:
    CIOSGraphics( UIView *viewRoot );
    ~CIOSGraphics();
    
    void Clear( int color ) const;
    void Present() const;
    
    void DrawPixel( int x, int y, int color ) const;
    void DrawLine( int startX, int startY, int stopX, int stopY, int color ) const;
	void DrawRect( int x, int y, int width, int height, int color ) const;
    
	int GetWidth()	const;
	int GetHeight() const;
    
protected:
    UIView *m_viewRoot;
};


UIColor* GetUIColorFromARGB( int argb );


#endif

