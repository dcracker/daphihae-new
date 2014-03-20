#include "stdafx.h"
#include "WindowsPlatform.h"
#include "WindowsGraphics.h"
#include "WindowsInput.h"
#include "WindowsFileIO.h"

WindowsPlatform::WindowsPlatform( WindowsGraphics* graphics )
	: mGraphics( graphics )
	, mInput( new WindowsInput() )
	, mFileIO( new WindowsFileIO() )
{
}


WindowsPlatform::~WindowsPlatform()
{
	if ( mGraphics != NULL ) {
		delete mGraphics;
	}
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
void WindowsPlatform::OnTouchEvent( void* args ) {
	mInput->PushTouchEvent( (const int*)args );
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