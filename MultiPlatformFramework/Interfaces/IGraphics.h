#ifndef IGraphics_H_
#define IGraphics_H_

class IGraphics {
public:
	virtual ~IGraphics() {}

	virtual void Present() const = 0;

	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual float GetAspectRatio() const = 0;
};

#endif	// IGraphics_H_
