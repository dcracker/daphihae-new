#pragma once
#include "../Common/CommonInput.h"

class WindowsInput : public CommonInput {
public:
	WindowsInput( const CommonTouchMessageHandler* touchHandler );
	~WindowsInput();

// IInput Interfaces
//	bool IsKeyPressed( int keyCode ) const;

	float GetAccelX() const;
	float GetAccelY() const;
	float GetAccelZ() const;

public:
	static void PushTouchEvent( CommonTouchMessageHandler* handler, HWND hWnd, UINT eventType, LPARAM param );

private:
	static const int cNumButtons = 1;
	static bool sIsButtonDown[cNumButtons];
};
