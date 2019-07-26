#pragma once
#include "SSelectModel.h"

class SAsyncSelect : public SSelectModel
{
public:
	LRESULT				MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual bool		Init();
public:
	SAsyncSelect(SOCKET sock);
	virtual ~SAsyncSelect();
};

