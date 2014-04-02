
#include "stdafx.h"

#include "CommonInput.h"
#include "logger.h"

#define LOG_TAG "CommonInput"

CommonInput::CommonInput()
{
	mTouchEventBuffer.clear();
	for ( int i=0; i < cMaxNumFingers; ++i ) {
		mTouchPoints[i].isTouched = false;
		mTouchPoints[i].x = 0;
		mTouchPoints[i].y = 0;
	}
}

CommonInput::~CommonInput() {
	mTouchEventBuffer.clear();
}

void CommonInput::PushTouchEvent( const int* eventParams ) {
//	LOG_INFO("CommonInput::PushTouchEvent %d, %d, %d, %d", eventParams[0], eventParams[1], eventParams[2], eventParams[3]);

	TouchEvent newEvent = ParseParams( eventParams );
	UpdateCurrentTouchPoints( newEvent );
	mTouchEventBuffer.push_back( newEvent );

	delete eventParams;
}

// IInput Interfaces
bool CommonInput::IsKeyPressed( int keyCode ) const {
	return false;
}

bool CommonInput::IsTouchDown( int id ) const {
	if ( IsVaildId( id ) == false ) {
		return false;
	}
	return mTouchPoints[id].isTouched;
}

int CommonInput::GetTouchX( int id ) const {
	if ( IsVaildId( id ) == false ) {
		return 0;
	}
	return mTouchPoints[id].x;
}

int CommonInput::GetTouchY( int id ) const {
	if ( IsVaildId( id ) == false ) {
		return 0;
	}
	return mTouchPoints[id].y;
}

const std::vector<TouchEvent>& CommonInput::GetTouchEvents() {
	static std::vector<TouchEvent> returnBuffer;
	mTouchEventBuffer.swap(returnBuffer);
	mTouchEventBuffer.clear();
//	LOG_INFO("CommonInput::GetTouchEvents() %d, %d", mTouchEventBuffer.size(), returnBuffer.size());
	return returnBuffer;
}

bool CommonInput::IsVaildId( int id ) {
	return (id >= 0) && (id < cMaxNumFingers);
}

TouchEvent CommonInput::ParseParams( const int* eventParams ) {
	TouchEvent newEvent;
	newEvent.type = (TouchEvent::EventType)eventParams[0];
	newEvent.id = eventParams[1];
	newEvent.x = eventParams[2];
	newEvent.y = eventParams[3];
	return newEvent;
}

void CommonInput::UpdateCurrentTouchPoints( const TouchEvent& event ) {
	if ( IsVaildId( event.id ) == false ) {
		return;
	}

	TouchPoint& current = mTouchPoints[event.id];

	if ( event.type == TouchEvent::TOUCH_UP ) {
		current.isTouched = false;
	}
	else if ( event.type == TouchEvent::TOUCH_DOWN ) {
		current.isTouched = true;
	}

	current.x = event.x;
	current.y = event.y;
}
