/*
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing This Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */
#include "stdafx.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#include "WindowsTimer.h"
#include "WindowsPlatform.h"
#include "WindowsGraphics.h"
#include "WindowsInput.h"

#include "Common/CommonTouchMessageHandler.h"
#include "Common/MainGameLoop.h"
#include "DaPhiHae.h"

MainGameLoop* loop = NULL;
CommonTouchMessageHandler* touchHandler = NULL;

bool	gActivate = false;
bool	keys[256];			// Array Used For The Keyboard Routine
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
bool	isLButtonDown = false;


LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	// Ask The User Which Screen Mode They Prefer
//	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	touchHandler = new CommonTouchMessageHandler();
	WindowsPlatform platformInstance(
		touchHandler
	);
	DaPhiHae gameInstance( &platformInstance );
	loop = new MainGameLoop( &gameInstance, &platformInstance, new WindowsTimer() );

	// Create Our OpenGL Window
	WindowsGraphics::CreateNewWindow( "NeHe's OpenGL Framework", 320, 480, 16, WndProc );
	MSG Message;									// Windows Message Structure
	while( GetMessage(&Message,0,0,0) ) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

/*	if (keys[VK_F1])						// Is F1 Being Pressed?
	{
		keys[VK_F1]=FALSE;					// If So Make Key FALSE
		KillGLWindow();						// Kill Our Current Window
		fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
		// Recreate Our OpenGL Window
		if (!CreateGLWindow("NeHe's OpenGL Framework",640,480,16,fullscreen))
		{
			return 0;						// Quit If Window Was Not Created
		}
	}*/

	// Shutdown
	return (Message.wParam);							// Exit The Program
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_CREATE:
		{
	//		printf( "WM_CREATE\n" );
			loop->PushMessage( MainGameLoop::MSG_WINDOW_SET, hWnd );
			return 0;
		}

		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
	//		printf( "WM_ACTIVATE  " );
			bool isActive = !HIWORD(wParam);
			if ( gActivate == isActive ) {
				return 0;
			}

	//		printf( isActive ? "Activate\n" : "Deactivate\n" );
			if (isActive)							// Check Minimization State
			{
				gActivate = true;
				loop->Start();						// Program Is Active
			}
			else
			{
				gActivate = false;
				loop->Stop();						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			loop->Stop();
			SAFE_DELETE( loop );
			SAFE_DELETE( touchHandler );

			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MOUSEMOVE:
		{
			WindowsInput::PushTouchEvent( touchHandler, hWnd, uMsg, lParam );
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			loop->PushMessage( MainGameLoop::MSG_WINDOW_SET, hWnd );
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}