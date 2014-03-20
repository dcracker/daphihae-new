#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLu32.lib")

#include "CommonHeaders.h"
#include "OpenGLCommons.h"

// GL_CLAMP_TO_EDGE is feature of OpenGL 1.2.
// but MS Windows officially serve OpenGL 1.1 only.
// if want to use GL_CLAMP_TO_EDGE then use GLEE or GLEW
#define GL_CLAMP_TO_EDGE GL_CLAMP