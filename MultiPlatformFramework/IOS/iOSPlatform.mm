
#include "iOSPlatform.h"


CIOSPlatform::CIOSPlatform()
{
#if 0
    m_Graphics = new CIOSGraphics( viewRoot );
#endif
}

CIOSPlatform::~CIOSPlatform()
{
#if 0
    if ( m_Graphics )
    {
        delete m_Graphics;
        m_Graphics = NULL;
    }
#endif
}


IInput* CIOSPlatform::GetInput() const
{
    return NULL;
}

const IFileIO* CIOSPlatform::GetFileIO() const
{
    return NULL;
}

const IGraphics* CIOSPlatform::GetGraphics() const
{
    return m_Graphics;
}
