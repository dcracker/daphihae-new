#ifndef CommonInput_H_
#define CommonInput_H_

#include "Interfaces/IInput.h"

class CommonInput: public IInput {
public:
	CommonInput();
	virtual ~CommonInput();

	void PushTouchEvent( const int* eventParams );

// IInput Interfaces
	bool IsKeyPressed( int keyCode ) const;
	bool IsTouchDown( int id ) const;

	int GetTouchX( int id ) const;
	int GetTouchY( int id ) const;

	const std::vector<TouchEvent>& GetTouchEvents();
private:
	static TouchEvent ParseParams( const int* eventParams );
	static bool IsVaildId( int id );
	void UpdateCurrentTouchPoints( const TouchEvent& event );

private:
	std::vector<TouchEvent> mTouchEventBuffer;

	struct TouchPoint {
		bool isTouched;
		int x;
		int y;
	};
	static const int cMaxNumFingers = 10;
	TouchPoint mTouchPoints[cMaxNumFingers];
};

#endif /* CommonInput_H_ */
