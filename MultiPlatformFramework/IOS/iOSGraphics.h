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
#include "Common/CommonHeaders.h"


class CIOSGraphics : public IGraphics
{
protected:
    void* m_viewRender;
    void* m_Context;
    void* m_DisplayLink;
    
    GLint m_nFBufferWidth;
    GLint m_nFBufferHeight;
    
    GLuint m_uFBufferDefault;
    GLuint m_uRBufferColor;
    GLuint m_uRBufferDepth;
    
    bool m_bUseDepthBuffer;
    
    float m_fRetinaScale;

public:
    CIOSGraphics();
    virtual ~CIOSGraphics();
    
    virtual void Present() const;
    
    virtual int GetWidth() const;
    virtual int GetHeight() const;
    virtual float GetAspectRatio() const;
    
    int AttachRenderView( void* viewRender, float fRetinaScale, bool bUseDepthBuffer=false );
    void DetachRenderView();
    void ResizeRenderView();
    bool isRenderViewReady();
    
    void startRenderLoop();
    void stopRenderLoop();
    
private:
    void createFramebuffer();
    void deleteFramebuffer();
};


#endif

