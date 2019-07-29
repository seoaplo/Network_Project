#pragma once
#include "SSendPacketPool.h"
#include "SRecvPacketPool.h"


class SPacketThread
{
public:
	SOCKET m_Sock;
	FD_SET  m_rSet;
	FD_SET  m_wSet;
	int m_addlen;

	DWORD	m_iThreadID;
	HANDLE	m_hThread;
	SmartMutex m_Mutex;

	DWORD			m_dwEndPos;
	DWORD			m_dwStartPos;
	DWORD			m_dwReadPos;
	DWORD			m_dwWritePos;

	char	m_szRecvBuffer[MAX_USER_BUFFER_SIZE];
	char	m_szPackStream[MAX_STREAM_SIZE];

public:
	bool Init();
	bool Frame();
	bool Release();
public:
	bool PacketProcess();
	void Put(char* pBuffer, DWORD dwByte);
private:
	bool Recv();
	bool Send();
public:
	SPacketThread();
	~SPacketThread();
};

