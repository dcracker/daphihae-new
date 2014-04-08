#ifndef CommonInput_H_
#define CommonInput_H_

#include "Interfaces/IInput.h"

class CommonTouchMessageHandler;

class CommonInput: public IInput {
public:
	CommonInput( const CommonTouchMessageHandler* touchHandler );
	virtual ~CommonInput();

// IInput Interfaces
	bool IsKeyPressed( int keyCode ) const;
	bool IsTouchDown( int id ) const;

	int GetTouchX( int id ) const;
	int GetTouchY( int id ) const;
private:
	const CommonTouchMessageHandler* mTouchHandler;
};

#endif /* CommonInput_H_ */
