#include <Windows.h>
#include "winapigame.h"

// -------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// -------------------------------------------------------------------------------------------------------

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wc;

	wc.hInstance	 = hInstance;
	wc.lpszClassName = "WindowApp";
	wc.lpfnWndProc	 = WndProc;
	wc.style		 = CS_DBLCLKS;
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName  = nullptr;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;


	if(!RegisterClassEx(&wc))
		{
		MessageBox(NULL, "Window Registration Failed!","Error!", MB_ICONEXCLAMATION | MB_OK);
		return (0);
		};

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,wc.lpszClassName,"Game in Life",WS_VISIBLE | WS_OVERLAPPEDWINDOW,10,10,610,380,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,nCmdShow);

	if(hwnd == NULL) 
		{
		MessageBox(NULL, "Window Creation Failed!","Error!", MB_ICONEXCLAMATION | MB_OK);
		return (0);
		};

	while (GetMessage(&msg, NULL, 0, 0) > 0)
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		};

	return (msg.wParam);
	};

// -------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
//static HWND buttons[38];

switch (Message)
	{
	case WM_CREATE :
		{
		//Creation_Dispatcher(buttons,hwnd);
		WinAPIGame G;
		}
		break;

	// ----------------------------------------------------------------------------------

	case WM_COMMAND :
		{
		//Main_Window_Dispatcher(hwnd,lParam,buttons);
		HDC hdc = GetDC(hwnd);
		//Menu_Dispatcher(hwnd, hdc, wParam);
		ReleaseDC(hwnd,hdc);
		}
		break;

	// ----------------------------------------------------------------------------------

	case WM_CLOSE :
		{
		DestroyWindow(hwnd);
		}

	// ----------------------------------------------------------------------------------

	case WM_DESTROY : 
		{
		PostQuitMessage(0);
		break;
		}

	// ----------------------------------------------------------------------------------
		
	default : return DefWindowProc(hwnd, Message, wParam, lParam);
	};

return (0);
};
