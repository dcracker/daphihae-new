#include "stdafx.h"
#include "CommonTouchMessageHandler.h"

#include "logger.h"

#define LOG_TAG "TouchHandler"

CommonTouchMessageHandler::CommonTouchMessageHandler()
{
	ZeroMemory( mTouchPoints, sizeof( TouchPoint ) * cMaxNumFingers );
}


CommonTouchMessageHandler::~CommonTouchMessageHandler()
{
}

void CommonTouchMessageHandler::ProcessTouchInput( TouchEventType type, int fingerId, int x, int y ) {
//	LOG_INFO( "%d [ %d ] : %d, %d", type, fingerId, x, y );
	if ( IsVaildId( fingerId ) == false ) {
		return;
	}

	TouchPoint& current = mTouchPoints[fingerId];

	if ( type == TouchEventType::TOUCH_UP ) {
		current.isTouched = false;
	}
	else {
		current.isTouched = true;
	}

	current.x = x;
	current.y = y;
}

bool CommonTouchMessageHandler::IsVaildId( int id ) {
	return (id >= 0) && (id < cMaxNumFingers);
}

bool CommonTouchMessageHandler::IsTouchDown( int id ) const {
	if ( IsVaildId( id ) == false ) {
		return false;
	}
	return mTouchPoints[id].isTouched;
}

int CommonTouchMessageHandler::GetTouchX( int id ) const {
	if ( IsVaildId( id ) == false ) {
		return 0;
	}
	return mTouchPoints[id].x;
}

int CommonTouchMessageHandler::GetTouchY( int id ) const {
	if ( IsVaildId( id ) == false ) {
		return 0;
	}
	return mTouchPoints[id].y;
}