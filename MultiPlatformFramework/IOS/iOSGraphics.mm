
#include "iOSGraphics.h"


CIOSGraphics::CIOSGraphics()
    : m_viewRender( NULL )
    , m_Context( NULL )
    , m_DisplayLink( NULL )
    , m_nFBufferWidth( 0 )
    , m_nFBufferHeight( 0 )
    , m_uFBufferDefault( 0 )
    , m_uRBufferColor( 0 )
    , m_uRBufferDepth( 0 )
    , m_bUseDepthBuffer( false )
    , m_fRetinaScale( 1.0f )
{
}

CIOSGraphics::~CIOSGraphics()
{
    if ( m_viewRender )
    {
        DetachRenderView();
    }
}


void CIOSGraphics::Present() const
{
//    NSLog( @"Present" );
    if ( m_Context != NULL )
    {
        EAGLContext* context = (__bridge EAGLContext*)m_Context;
//        [EAGLContext setCurrentContext:context];

        if ( !m_uFBufferDefault )
        {
            NSLog( @"no frame buffer" );
        }
        
        // draw something

        glBindRenderbuffer( GL_RENDERBUFFER, m_uRBufferColor );
        [context presentRenderbuffer:GL_RENDERBUFFER];
        
        glBindFramebuffer( GL_FRAMEBUFFER, m_uFBufferDefault );
    }
    else
    {
        NSLog( @"Context not set" );
    }
}


int CIOSGraphics::GetWidth() const
{
    if ( !m_viewRender )
    {
        return 0;
    }
    UIView* view = (__bridge UIView*)m_viewRender;
    return (int)(view.frame.size.width * m_fRetinaScale);
}

int CIOSGraphics::GetHeight() const
{
    if ( !m_viewRender )
    {
        return 0;
    }
    UIView* view = (__bridge UIView*)m_viewRender;
    return (int)(view.frame.size.height * m_fRetinaScale);
}

float CIOSGraphics::GetAspectRatio() const
{
    if ( !m_viewRender )
    {
        return 0.0f;
    }
    UIView* view = (__bridge UIView*)m_viewRender;
    return (view.frame.size.width / view.frame.size.height);
}


int CIOSGraphics::AttachRenderView( void* viewRender, float fRetinaScale, bool bUseDepthBuffer )
{
    if ( m_viewRender )
    {
        NSLog( @"multiple call" );
        return -1;
    }
    
    UIView* view = (__bridge UIView*)viewRender;
    
    // create context
    EAGLContext* context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
    if ( !context || ![EAGLContext setCurrentContext:context] )
    {
        NSLog( @"could not create context" );
        return -2;
    }
    m_Context = (__bridge void*)context;
    
    // setting layer's properties
    CAEAGLLayer* eaglLayer = (CAEAGLLayer*)view.layer;
    eaglLayer.opaque = YES;
    eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                    @(NO), kEAGLDrawablePropertyRetainedBacking,
                                    kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];

    // setting local properties
    m_bUseDepthBuffer = bUseDepthBuffer;
    m_fRetinaScale = fRetinaScale;
    
    m_uFBufferDefault = 0;
    m_uRBufferColor = 0;
    m_uRBufferDepth = 0;
    
    m_viewRender = viewRender;
    
    // create frame buffer
    createFramebuffer();

    return 1;
}

void CIOSGraphics::DetachRenderView()
{
    if ( m_viewRender )
    {
        deleteFramebuffer();
    }
    m_viewRender = NULL;
    m_Context = NULL;
    m_DisplayLink = NULL;
}

bool CIOSGraphics::isRenderViewReady()
{
    return (m_viewRender != NULL);
}

void CIOSGraphics::ResizeRenderView()
{
    if ( m_viewRender && m_uFBufferDefault )
    {
        deleteFramebuffer();
        createFramebuffer();
    }
}

void CIOSGraphics::startRenderLoop()
{
//    if ( !m_DisplayLink )
    {
//        UIView* view = (__bridge UIView*)m_viewRender;
//        CADisplayLink* displayLink = [view.window.screen displayLinkWithTarget:view selector:@selector( drawRect: )];
//        [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
//        m_DisplayLink = (__bridge void*)displayLink;
        
        EAGLContext* context = (__bridge EAGLContext*)m_Context;
        [EAGLContext setCurrentContext:context];
        glBindFramebuffer( GL_FRAMEBUFFER, m_uFBufferDefault );

        NSLog( @"Starting render loop" );
    }
}

void CIOSGraphics::stopRenderLoop()
{
//    if ( m_DisplayLink )
//    {
//        CADisplayLink* displayLink = (__bridge CADisplayLink*)m_DisplayLink;
//        [displayLink invalidate];
//        displayLink = nil;
//        m_DisplayLink = NULL;
        NSLog( @"Stopping render loop" );
//    }
}



#pragma mark private methods

void CIOSGraphics::createFramebuffer()
{
    assert( m_uFBufferDefault == 0 );
    
    NSLog( @"EGLTView: creating Framebuffer" );
    
    glGenFramebuffers( 1, &m_uFBufferDefault );
    glBindFramebuffer( GL_FRAMEBUFFER, m_uFBufferDefault );
    
    glGenRenderbuffers( 1, &m_uRBufferColor );
    glBindRenderbuffer( GL_RENDERBUFFER, m_uRBufferColor );
    
    EAGLContext* context = (__bridge EAGLContext*)m_Context;
    CAEAGLLayer* eaglLayer = (CAEAGLLayer *)((__bridge UIView*)m_viewRender).layer;
    [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:eaglLayer];

    glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &m_nFBufferWidth );
    glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &m_nFBufferHeight );
    
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_uRBufferColor );
    
    if ( m_bUseDepthBuffer )
    {
        glGenRenderbuffers( 1, &m_uRBufferDepth );
        glBindRenderbuffer( GL_RENDERBUFFER, m_uRBufferDepth );
        
        glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_nFBufferWidth, m_nFBufferHeight );
        
        glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_uRBufferDepth );
    }
    
    if ( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
    {
        NSLog( @"Failed to make complete framebuffer object %x", glCheckFramebufferStatus( GL_FRAMEBUFFER ) );
    }
}

void CIOSGraphics::deleteFramebuffer()
{
    if ( m_Context )
    {
        EAGLContext* context = (__bridge EAGLContext*)m_Context;
        [EAGLContext setCurrentContext:context];
        
        if ( m_uFBufferDefault )
        {
            glDeleteFramebuffers( 1, &m_uFBufferDefault );
            m_uFBufferDefault = 0;
        }
        if ( m_uRBufferColor )
        {
            glDeleteRenderbuffers( 1, &m_uRBufferColor );
            m_uRBufferColor = 0;
        }
        if ( m_uRBufferDepth )
        {
            glDeleteRenderbuffers( 1, &m_uRBufferDepth );
            m_uRBufferDepth = 0;
        }
    }
}



