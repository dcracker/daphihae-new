#include "stdafx.h"
#include "WindowsPlatform.h"
#include "WindowsGraphics.h"
#include "WindowsInput.h"
#include "WindowsFileIO.h"

WindowsPlatform::WindowsPlatform( const CommonTouchMessageHandler* touchHandler )
	: mGraphics( new WindowsGraphics() )
	, mInput( new WindowsInput( touchHandler ) )
	, mFileIO( new WindowsFileIO() )
{
}


WindowsPlatform::~WindowsPlatform()
{
	SAFE_DELETE( mGraphics );
	SAFE_DELETE( mInput );
	SAFE_DELETE( mFileIO );
}

const IGraphics* WindowsPlatform::GetGraphics() const {
	return mGraphics;
}

IInput* WindowsPlatform::GetInput() const {
	return mInput;
}

const IFileIO* WindowsPlatform::GetFileIO() const {
	return mFileIO;
}

void WindowsPlatform::OnWindowChanged( void* args ) {
	mGraphics->SetWindow( (HWND)args );
	mGraphics->Resize();
}

void WindowsPlatform::OnResume() {
	mGraphics->CreateRenderingContext();
}

void WindowsPlatform::OnPause() {
	mGraphics->DestroyRenderingContext();
}

void WindowsPlatform::OnPresent() const {
	mGraphics->Present();
}

void WindowsPlatform::OnTakeABreak() const {
	Sleep(1);
}