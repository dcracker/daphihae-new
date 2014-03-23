
#include "iOSGraphics.h"


CIOSGraphics::CIOSGraphics()
{
#if 0
    m_viewRoot = nil;
    if ( viewRoot )
    {
        m_viewRoot = viewRoot;
    }
    else
    {
        NSLog( @"error with root view. %s", __FUNCTION__ );
    }
#endif
}

CIOSGraphics::~CIOSGraphics()
{
#if 0
    if ( m_viewRoot )
    {
        m_viewRoot = nil;
    }
#endif
}


int CIOSGraphics::GetWidth() const
{
    return 0;
}

int CIOSGraphics::GetHeight() const
{
    return 0;
}

float CIOSGraphics::GetAspectRatio() const
{
    return 0.0f;
}
