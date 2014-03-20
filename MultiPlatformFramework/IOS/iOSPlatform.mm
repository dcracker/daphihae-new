
#include "iOSPlatform.h"


CIOSPlatform::CIOSPlatform( UIView *viewRoot )
{
    m_Graphics = new CIOSGraphics( viewRoot );
}

CIOSPlatform::~CIOSPlatform()
{
    if ( m_Graphics )
    {
        delete m_Graphics;
        m_Graphics = NULL;
    }
}