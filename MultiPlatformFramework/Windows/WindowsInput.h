#pragma once
#include "../Common/CommonInput.h"

class WindowsInput : public CommonInput {
public:
	WindowsInput();
	~WindowsInput();

// IInput Interfaces
//	bool IsKeyPressed( int keyCode ) const;

	float GetAccelX() const;
	float GetAccelY() const;
	float GetAccelZ() const;

public:
	static void* CreateTouchParam( int eventType, LPARAM param );
};
