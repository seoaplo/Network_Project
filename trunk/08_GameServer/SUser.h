#pragma once
#include "SServerStd.h"
#include "Protocol.h"
#include "SPacketPool.h"


class SUser
{
private:
	bool	m_bReady;
	bool	m_bConnect;
	bool	m_bDisConnect;
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
	// Setter
	void SetConnect(bool bConnect = true)
	{
		SScopeRock_Mutex Lock(m_Mutex);
		m_bConnect = bConnect;
	}
	void SetDisConnect(bool bDisConnect = true)
	{
		SScopeRock_Mutex Lock(m_Mutex);
		m_bDisConnect = bDisConnect;
	}
	void SetReady(bool bReady = true)
	{
		SScopeRock_Mutex Lock(m_Mutex);
		m_bReady = bReady;
	}
	void SetNumber(int iNum)
	{
		SScopeRock_Mutex Lock(m_Mutex);
		m_iNum = iNum;
	}
	void SetSocket(SOCKET sock)
	{
		SScopeRock_Mutex Lock(m_Mutex);
		m_sock = sock;
	}
	void SetSockAddr(SOCKADDR_IN sockaddr)
	{
		SScopeRock_Mutex Lock(m_Mutex);
		m_addr = sockaddr;
	}
	void SetName(C_STR Name)
	{
		SScopeRock_Mutex Lock(m_Mutex);
		m_UserName = Name;
	}
public:
	// Getter
	const bool& GetConnect()
	{
		SScopeRock_Mutex Lock(m_Mutex);
		return m_bConnect;
	}
	const bool& GetDisConnect()
	{
		SScopeRock_Mutex Lock(m_Mutex);
		return m_bDisConnect;
	}
	const bool& GetReady()
	{
		SScopeRock_Mutex Lock(m_Mutex);
		return m_bReady;
	}
	const int& GetNumber()
	{
		SScopeRock_Mutex Lock(m_Mutex);
		return m_iNum;
	}
	const SOCKET& GetSocket()
	{
		SScopeRock_Mutex Lock(m_Mutex);
		return m_sock;
	}
	const SOCKADDR_IN& GetSockAddr()
	{
		SScopeRock_Mutex Lock(m_Mutex);
		return m_addr;
	}
	const C_STR& GetName()
	{
		SScopeRock_Mutex Lock(m_Mutex);
		return m_UserName;
	}
public:
	SUser();
	~SUser();
};