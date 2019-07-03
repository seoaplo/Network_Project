#pragma once
#include "SSelectModel.h"

class SAsyncSelect : public SSelectModel
{
public:
	LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	bool		Init();
public:
	SAsyncSelect(HWND hWnd);
	virtual ~SAsyncSelect();
};

