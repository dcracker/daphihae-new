#pragma once
#include "../Interfaces/IGraphics.h"

class WindowsGraphics : public IGraphics {
public:
	WindowsGraphics();
	~WindowsGraphics();

	void Present()	const	{ SwapBuffers( hDC ); }

	int GetWidth()	const			{ return mWidth; }
	int GetHeight()	const			{ return mHeight; }
	float GetAspectRatio() const	{ return (float)mWidth / (float)mHeight; }

public:
	/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
	 *	title			- Title To Appear At The Top Of The Window				*
	 *	width			- Width Of The GL Window Or Fullscreen Mode				*
	 *	height			- Height Of The GL Window Or Fullscreen Mode			*
	 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*/
	static HWND CreateNewWindow( char* title, int width, int height, int bits, WNDPROC proc );
	static void DestroyWindow( HWND hWnd );

public:
	bool CreateRenderingContext();
	void DestroyRenderingContext();

	void SetWindow( HWND hWnd );
	void Resize();

private:
	int		mWidth;
	int		mHeight;
	
	bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

	HDC			hDC;		// Private GDI Device Context
	HGLRC		hRC;		// Permanent Rendering Context
	HWND		m_hWnd;		// Holds Our Window Handle
};