#pragma once

#include <assert.h>

#define SAFE_DELETE( p )	\
	if ( (p) != NULL ) {	\
		delete (p);			\
		(p) = NULL;			\
	}
