#pragma once
#include "SServerStd.h"
#include "Protocol.h"

class SSelectModel
{
public:
	HWND	m_hWnd;
	SOCKET	m_Sock;
	std::basic_string<char> UserName;

	int		m_iRecvByte;
	char	m_szRecvBuffer[PACKET_MAX_DATA_SIZE + PACKET_HEADER_SIZE];

public:
	virtual bool	Init() { return true; }
	virtual bool	Frame() { return true; }
	virtual bool	Render() { return true; };
	virtual bool	Release() { return true; };
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return 1;
	}
	bool	RecvData();
	bool	RecvMsg(SOCKET sock, char* pBuffer, int iNumDataByte);
	bool	SendMsg(SOCKET sock, int type, char* data, int iSize);
	bool	SendMsg(UPACKET& packet);
public:
	SSelectModel();
	virtual ~SSelectModel();
};

