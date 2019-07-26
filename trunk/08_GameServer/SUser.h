#pragma once
#include "SServerStd.h"
#include "Protocol.h"
#include "SPacketPool.h"


class SUser
{
public:
	bool	m_bReady;
	bool	bConnect;

	int		m_iNum;

	SOCKET		m_sock;
	SOCKADDR_IN m_addr;
	C_STR		m_UserName;

	DWORD			m_dwEndPos;
	DWORD			m_dwStartPos;
	DWORD			m_dwReadPos;
	DWORD			m_dwWritePos;

	char			m_szRecvBuffer[MAX_USER_BUFFER_SIZE];
	char			m_szPackStream[MAX_STREAM_SIZE];
	
	SmartMutex m_Mutex;
	std::queue<PACKET> m_SendPacketPool;
public:
	bool Init();
	bool Release();
public:
	void Put(char* pBuffer, DWORD dwByte);
	bool Recv();
	bool PushSendPacket(PACKET pack);
	bool Send();
public:
	SUser();
	~SUser();
};