
#include "iOSGraphics.h"


CIOSGraphics::CIOSGraphics( UIView *viewRoot )
{
    m_viewRoot = nil;
    if ( viewRoot )
    {
        m_viewRoot = viewRoot;
    }
    else
    {
        NSLog( @"error with root view. %s", __FUNCTION__ );
    }
}

CIOSGraphics::~CIOSGraphics()
{
    if ( m_viewRoot )
    {
        m_viewRoot = nil;
    }
}


void CIOSGraphics::Clear( int color ) const
{
    [m_viewRoot.subviews makeObjectsPerformSelector:@selector( removeFromSuperview )];
    [m_viewRoot setBackgroundColor:GetUIColorFromARGB( color )];
}

void CIOSGraphics::Present() const
{
}


void CIOSGraphics::DrawPixel( int x, int y, int color ) const
{
    DrawRect( x, y, 1, 1, color );
}

void CIOSGraphics::DrawLine( int startX, int startY, int stopX, int stopY, int color ) const
{
//    DrawRect( startX, startY, stopX - startX, stopY - startY, color );
}

void CIOSGraphics::DrawRect( int x, int y, int width, int height, int color ) const
{
    UIView *viewPaint = [[UIView alloc] initWithFrame:CGRectMake( x, y, width, height )];
    [viewPaint setBackgroundColor:GetUIColorFromARGB( color )];
    [m_viewRoot addSubview:viewPaint];
}


int CIOSGraphics::GetWidth() const
{
    return (int)m_viewRoot.frame.size.width;
}

int CIOSGraphics::GetHeight() const
{
    return (int)m_viewRoot.frame.size.height;
}


UIColor* GetUIColorFromARGB( int argb )
{
    int blue = argb & 0xff;
    int green = (argb >> 8) & 0xff;
    int red = (argb >> 16) & 0xff;
    int alpha = (argb >> 24) & 0xff;
    
    return [UIColor colorWithRed:(red / 255.0f) green:(green / 255.0f)
                            blue:(blue / 255.0f) alpha:(alpha / 255.0f)];
}