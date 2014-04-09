#ifndef ANDROIDINPUT_H_
#define ANDROIDINPUT_H_

#include "../Common/CommonInput.h"

class AndroidInput : public CommonInput {
public:
	AndroidInput( const CommonTouchMessageHandler* touchHandler );
	~AndroidInput();

// IInput Interfaces
//	bool IsKeyPressed( int keyCode ) const;

	float GetAccelX() const;
	float GetAccelY() const;
	float GetAccelZ() const;
};
#endif /* ANDROIDINPUT_H_ */
