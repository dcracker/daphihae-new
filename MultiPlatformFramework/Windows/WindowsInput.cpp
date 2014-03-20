#include "stdafx.h"
#include "WindowsInput.h"

WindowsInput::WindowsInput() {

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

void* WindowsInput::CreateTouchParam( int eventType, LPARAM lParam ) {
	int* touchParams = new int[4];
	touchParams[0] = eventType;
	touchParams[1] = 0;
	touchParams[2] = LOWORD( lParam );
	touchParams[3] = HIWORD( lParam );
	return (void*)touchParams;
}