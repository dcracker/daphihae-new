#ifndef IINPUT_H_
#define IINPUT_H_

class IInput {
public:

public:
	virtual ~IInput() {}

	virtual bool IsKeyPressed( int keyCode ) const = 0;

	virtual bool IsTouchDown( int id ) const = 0;
	virtual int GetTouchX( int id ) const = 0;
	virtual int GetTouchY( int id ) const = 0;

	virtual float GetAccelX() const = 0;
	virtual float GetAccelY() const = 0;
	virtual float GetAccelZ() const = 0;
};
#endif /* IINPUT_H_ */
