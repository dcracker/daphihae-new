#pragma once

#include <stdio.h>

#define LOG_INFO(...) \
	printf( "%s : ", LOG_TAG ); \
	printf( __VA_ARGS__ ); \
	printf( "\n");

#define LOG_ERROR(...) \
	fprintf( stderr, "%s", LOG_TAG ); \
	fprintf( stderr, __VA_ARGS__ ); \
	fprintf( stderr, "\n" );