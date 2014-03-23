#pragma once

#include <assert.h>

#ifdef PLATFORM_IOS
#include <OpenGLES/ES1/gl.h>
#endif

#define SAFE_DELETE( p )	\
	if ( (p) != NULL ) {	\
		delete (p);			\
		(p) = NULL;			\
	}
