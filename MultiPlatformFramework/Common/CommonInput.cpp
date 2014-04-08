
#include "stdafx.h"

#include "CommonInput.h"
#include "CommonTouchMessageHandler.h"

CommonInput::CommonInput( const CommonTouchMessageHandler* touchHandler )
	: mTouchHandler( touchHandler )
{
	assert( touchHandler != NULL );
}

CommonInput::~CommonInput() {
	mTouchHandler = NULL;
}

// IInput Interfaces
bool CommonInput::IsKeyPressed( int keyCode ) const {
	return false;
}

bool CommonInput::IsTouchDown( int id ) const {
	return mTouchHandler->IsTouchDown( id );
}

int CommonInput::GetTouchX( int id ) const {
	return mTouchHandler->GetTouchX( id );
}

int CommonInput::GetTouchY( int id ) const {
	return mTouchHandler->GetTouchY( id );
}