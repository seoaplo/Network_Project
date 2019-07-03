#pragma once
#include "STimer.h"
#include "SDirectWrite.h"
#include "SInputManager.h"
#include "Swindow.h"
#include "SSoundManager.h"
#include "SImageManager.h"
#include "SSpriteManager.h"

class SCore	: public SWindow
{
public:
	// CoreFrameWork
	bool	CoreInit();
	bool	CoreFrame();
	bool	CoreRender();
	bool	CoreRelease();

	// GameFrameWork

	virtual bool BeginInit();
	virtual bool BeginFrame();
	virtual	bool BeginRender();
	virtual bool BeginRelease();

	virtual bool Init();
	virtual bool Frame();
	virtual	bool Render();
	virtual bool Release();

	virtual bool EndInit();
	virtual bool EndFrame();
	virtual	bool EndRender();
	virtual bool EndRelease();

	virtual int WindowProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

	bool Run();
public:
	SCore();
	~SCore();
};

//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
//{
//	SCore g_Core;
//	if (!g_Core.InitWindow(hInstance, nCmdShow, const_cast<TCHAR*>(L"SoundTest"), g_Core.m_IsFullScreenMode))
//	{
//		MessageBox(0, _T("Sample  �ʱ�ȭ ����"), _T("Fatal error"), MB_OK);
//		return 0;
//	}
//	ShowCursor(TRUE);
//	g_Core.Run();
//	return 1;
//}