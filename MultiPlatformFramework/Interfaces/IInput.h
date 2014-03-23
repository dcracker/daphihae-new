#ifndef IINPUT_H_
#define IINPUT_H_

#include <vector>

struct TouchEvent {
	enum EventType {
		TOUCH_DOWN	= 0,
		TOUCH_UP	= 1,
		TOUCH_DRAG	= 2
	};

	EventType type;
	int id;
	int x, y;
};

// just add for explicit compatibility (C style) - kang
typedef struct TouchEvent TouchEvent;


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

	virtual const std::vector<TouchEvent>& GetTouchEvents() = 0;
};
#endif /* IINPUT_H_ */
