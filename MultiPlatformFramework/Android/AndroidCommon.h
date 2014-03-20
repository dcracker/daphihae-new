#ifndef ANDROIDCOMMON_H_
#define ANDROIDCOMMON_H_
// unfortunately NDK does not support PCH yet.

#include <EGL/egl.h>
#include <GLES/gl.h>

// adaptations for egl
#define glFrustum glFrustumf
#define glOrtho	glOrthof

#include "CommonHeaders.h"
#include "OpenGLCommons.h"

#endif	// ANDROIDCOMMON_H_
