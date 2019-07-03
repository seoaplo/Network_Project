#pragma once
#include "SServerStd.h"
#include "Protocol.h"

class SSelectModel
{
public:
	HWND	m_hWnd;
	SOCKET	m_Sock;
	std::basic_string<char> UserName;
public:
	virtual bool	Init() { return true; }
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return 1;
	}
	bool	RecvMsg(SOCKET sock, char* pBuffer, int iNumDataByte);
	bool	SendMsg(SOCKET sock, int type, char* data, int iSize);
public:
	SSelectModel();
	virtual ~SSelectModel();
};

