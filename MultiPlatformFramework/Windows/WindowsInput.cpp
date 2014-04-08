#include "stdafx.h"
#include "WindowsInput.h"
#include "Common/CommonTouchMessageHandler.h"

bool WindowsInput::sIsButtonDown[WindowsInput::cNumButtons] = { false };//, false, false };

WindowsInput::WindowsInput( const CommonTouchMessageHandler* touchHandler ) 
	: CommonInput( touchHandler )
{
	
}

WindowsInput::~WindowsInput() {

}

float WindowsInput::GetAccelX() const {
	return 0;
}

float WindowsInput::GetAccelY() const {
	return 0;
}

float WindowsInput::GetAccelZ() const {
	return 0;
}

void WindowsInput::PushTouchEvent( CommonTouchMessageHandler* handler, HWND hWnd, UINT message, LPARAM param ) {
	short x = LOWORD( param );
	short y = HIWORD( param );

	if ( x < 0 ) {
		x = 0;
	}

	if ( y < 0 ) {
		y = 0;
	}

	switch ( message ) {
	case WM_LBUTTONDOWN:
		sIsButtonDown[0] = true;
		handler->ProcessTouchInput( TouchEventType::TOUCH_DOWN, 0, x, y );
		SetCapture( hWnd );
		break;

	case WM_LBUTTONUP:
		sIsButtonDown[0] = false;
		handler->ProcessTouchInput( TouchEventType::TOUCH_UP, 0, x, y );
		ReleaseCapture();
		return;

	case WM_MOUSEMOVE:
		for ( int i=0; i < cNumButtons; ++i ) {
			if ( sIsButtonDown[i] == true ) {
				handler->ProcessTouchInput( TouchEventType::TOUCH_DRAG, i, x, y );
			}
		}
		return;
	}

}