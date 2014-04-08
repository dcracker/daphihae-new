#pragma once

enum TouchEventType {
	TOUCH_DOWN	= 0,
	TOUCH_UP	= 1,
	TOUCH_DRAG	= 2
};

class CommonTouchMessageHandler
{
public:

public:
	CommonTouchMessageHandler();
	~CommonTouchMessageHandler();

	void ProcessTouchInput( TouchEventType type, int fingerId, int x, int y );
	
public:
	bool IsTouchDown( int id ) const;

	int GetTouchX( int id ) const;
	int GetTouchY( int id ) const;

private:
	static bool IsVaildId( int id );

private:
	struct TouchPoint {
		bool isTouched;
		int x;
		int y;
	};
	static const int cMaxNumFingers = 10;
	TouchPoint mTouchPoints[cMaxNumFingers];
};

