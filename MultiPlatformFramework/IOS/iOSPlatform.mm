
#include "iOSPlatform.h"


CIOSPlatform::CIOSPlatform( CIOSGraphics* graphics )
    : m_Graphics( graphics )
{
    m_Input = new CIOSInput();
    m_FileIO = new CIOSFileIO();
}

CIOSPlatform::~CIOSPlatform()
{
    delete m_FileIO;
    delete m_Input;
}


IInput* CIOSPlatform::GetInput() const
{
    return m_Input;
}

const IFileIO* CIOSPlatform::GetFileIO() const
{
    return m_FileIO;
}

const IGraphics* CIOSPlatform::GetGraphics() const
{
    return m_Graphics;
}

const IAudio* CIOSPlatform::GetAudio() const
{
    return NULL;
}


#pragma mark implementations of listener

void CIOSPlatform::OnWindowChanged( void *args )
{
    m_Graphics->ResizeRenderView();
}

void CIOSPlatform::OnTouchEvent( void *args )
{
    m_Input->PushTouchEvent( (const int*)args );
}

void CIOSPlatform::OnResume()
{
    m_Graphics->startRenderLoop();
}

void CIOSPlatform::OnPause()
{
    m_Graphics->stopRenderLoop();
}

void CIOSPlatform::OnPresent() const
{
    m_Graphics->Present();
}

void CIOSPlatform::OnTakeABreak() const
{
}


