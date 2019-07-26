#pragma once
#include "SNetWork.h"
#include "Client/SCore.h"


class Sample : public SCore
{
public:
	SNetWork	m_Network;
	HWND		m_hSubWindow;
	HWND		m_hEdit;
	HWND		m_hButton;
	HWND		m_hList;

public:
	bool		Init();
	bool		PreFrame();
	bool		Frame();
	bool		PostFrame();
	bool		Release();
	bool		PacketProcess();

public:
	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	Sample();
	~Sample();
};

