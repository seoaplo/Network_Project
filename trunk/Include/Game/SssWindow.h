#pragma once
#include "Ssslibheader.h"
class SssWindow
{
public:
	HINSTANCE	MyhInstance;
	HWND		MyhWindow;
	RECT		MyClientRect;
	RECT		MyWindowRect;
public:
				bool			SetWindow(HINSTANCE hInstance, const TCHAR* lpszSetName);
				bool			InitWindow(const TCHAR* lpszSetName, int nCmdLine);
virtual			bool			Run();
virtual			LRESULT			WindowProc(HWND hWindow, UINT Messege, WPARAM wParam, LPARAM lParam);

public:
	SssWindow();
	virtual ~SssWindow();
};

#define SSSWINDOWSTART int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevinstnace, TCHAR* lpszCmdLine, int nCmdShow) {	SssSampler Window;
#define SSSWINDOWWORK(STR)	if (!Window.SetWindow(hInstance, L#STR)){return 0;}	if (!Window.InitWindow(L#STR, nCmdShow))	{		return 0;	}	Window.Run();	return 0;
#define SSSWINDOWEND	}
#define SSSWINDOW(STR) SSSWINDOWSTART SSSWINDOWWORK(STR) SSSWINDOWEND