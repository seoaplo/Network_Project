#pragma once
#include "SJoinThread.h"
#include "SGameThread.h"
#include "SPacketThread.h"

class SServer
{
public:
	WSADATA m_wsa;
	SOCKET	m_listensock;
	
	SJoinThread		m_JoinThread;
	SGameThread		m_GameThread;
	SPacketThread	m_PakcetThread;
public:
	bool Init();
	bool Frame();
	bool Release();

	bool Run();
public:
	SServer();
	~SServer();
};

