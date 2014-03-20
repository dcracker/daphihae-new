#ifndef AndroidGraphics_H_
#define AndroidGraphics_H_

#include <jni.h>
#include "../Interfaces/IGraphics.h"

class ANativeWindow;
class AndroidGraphics : public IGraphics {
public:
	AndroidGraphics();
	~AndroidGraphics();

	void Present()	const;

	int GetWidth()	const			{ return mWidth; }
	int GetHeight() const			{ return mHeight; }
	float GetAspectRatio() const	{ return (float)mWidth / (float)mHeight; }

public:
	// android window, supported by NDK r5 and newer
	bool InitializeEGLContext();
	bool SetWindow( ANativeWindow* window );
	void DestroyEGLContext();
	bool IsValid() { return _display != EGL_NO_DISPLAY; }

private:
	EGLDisplay _display;
	EGLSurface _surface;
	EGLContext _context;

	int		mWidth;
	int		mHeight;

	ANativeWindow* mWindow;
};

#endif	// AndroidGraphics_H_
