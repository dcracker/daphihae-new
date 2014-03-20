#ifndef IGame_H_
#define IGame_H_

class IGame {
public:
	virtual ~IGame() {}

	virtual void Resume() = 0;
	virtual void Pause() = 0;

	virtual void Update( float deltaTime ) = 0;
	virtual void Render() const = 0;
};

#endif	// IGame_H_
