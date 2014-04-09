#include "stdafx.h"
#include "AndroidInput.h"

AndroidInput::AndroidInput( const CommonTouchMessageHandler* touchHandler )
	: CommonInput( touchHandler )
{
}

AndroidInput::~AndroidInput() {

}

float AndroidInput::GetAccelX() const {
	return 0;
}

float AndroidInput::GetAccelY() const {
	return 0;
}

float AndroidInput::GetAccelZ() const {
	return 0;
}
