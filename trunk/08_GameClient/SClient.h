#pragma once
#include "SPacketThread.h"

class SClient
{
public:
	WSADATA m_wsa;
	SOCKET	m_listensock;

	SPacketThread	m_PakcetThread;
public:
	bool Init();
	bool Frame();
	bool Release();
public:
	SClient();
	~SClient();
};

