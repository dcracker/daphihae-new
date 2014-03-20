#include "stdafx.h"
#include "AndroidGraphics.h"

#include "logger.h"
#include <android/native_window.h> // requires ndk r5 or newer

#define LOG_TAG "AndroidGraphics"

AndroidGraphics::AndroidGraphics()
	: _display( EGL_NO_DISPLAY )
	, _surface( EGL_NO_SURFACE )
	, _context( EGL_NO_CONTEXT )
	, mWidth( 0 )
	, mHeight( 0 )
	, mWindow( NULL )
{
}

AndroidGraphics::~AndroidGraphics() {
	mWindow = NULL;
}

bool AndroidGraphics::SetWindow( ANativeWindow* window ) {
	mWindow = window;
	LOG_INFO( "SetWindow %p", window );
	return InitializeEGLContext();
}

bool AndroidGraphics::InitializeEGLContext() {
	if ( mWindow == NULL ) {
		return false;
	}

    const EGLint attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
    };
    EGLDisplay display;
    EGLConfig config;    
    EGLint numConfigs;
    EGLint format;
    EGLSurface surface;
    EGLContext context;
    EGLint width;
    EGLint height;
    GLfloat ratio;
    
    LOG_INFO("Initializing context");
    
    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        LOG_ERROR("eglGetDisplay() returned error %d", eglGetError());
        return false;
    }
    if (!eglInitialize(display, 0, 0)) {
        LOG_ERROR("eglInitialize() returned error %d", eglGetError());
        return false;
    }

    if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs)) {
        LOG_ERROR("eglChooseConfig() returned error %d", eglGetError());
        DestroyEGLContext();
        return false;
    }

    if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format)) {
        LOG_ERROR("eglGetConfigAttrib() returned error %d", eglGetError());
        DestroyEGLContext();
        return false;
    }

    ANativeWindow_setBuffersGeometry(mWindow, 0, 0, format);

    if (!(surface = eglCreateWindowSurface(display, config, mWindow, 0))) {
        LOG_ERROR("eglCreateWindowSurface() returned error %d", eglGetError());
        DestroyEGLContext();
        return false;
    }
    
    if (!(context = eglCreateContext(display, config, 0, 0))) {
        LOG_ERROR("eglCreateContext() returned error %d", eglGetError());
        DestroyEGLContext();
        return false;
    }
    
    if (!eglMakeCurrent(display, surface, surface, context)) {
        LOG_ERROR("eglMakeCurrent() returned error %d", eglGetError());
        DestroyEGLContext();
        return false;
    }

    if (!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
        !eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
        LOG_ERROR("eglQuerySurface() returned error %d", eglGetError());
        DestroyEGLContext();
        return false;
    }

    _display = display;
    _surface = surface;
    _context = context;

	mWidth = width;
	mHeight = height;

    return true;
}

void AndroidGraphics::DestroyEGLContext() {
	LOG_INFO("Destroying context");

    eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(_display, _context);
    eglDestroySurface(_display, _surface);
    eglTerminate(_display);
    
    _display = EGL_NO_DISPLAY;
    _surface = EGL_NO_SURFACE;
    _context = EGL_NO_CONTEXT;
}

void AndroidGraphics::Present()	const {
	if (_display != EGL_NO_DISPLAY && !eglSwapBuffers(_display, _surface)) {
        LOG_ERROR("eglSwapBuffers() returned error %d", eglGetError());
    }
}
