#include "SServer.h"

bool SServer::Init()
{
	
	WSAStartup(MAKEWORD(2, 2), &m_wsa);

	I_UserPool.Init();
	I_JoinPacketPool.Init();
	I_GamePacketPool.Init();

	m_PakcetThread.Init();
	m_JoinThread.Init();
	m_GameThread.Init();
	return true;
}
bool SServer::Frame()
{
	if (m_JoinThread.Frame() == false) return false;
	if (m_GameThread.Frame() == false) return false;
	if (m_PakcetThread.Frame() == false) return false;
	return true;
}
bool SServer::Release()
{
	m_JoinThread.Release();
	m_GameThread.Release();
	m_PakcetThread.Release();
	closesocket(m_listensock);
	WSACleanup();
	return true;
}

bool SServer::Run()
{
	bool SuccessInit = true;
	SuccessInit =Init();

	while (SuccessInit)
	{
		if (Frame() == false) break;
	}

	return Release();
}

SServer::SServer()
{
}


SServer::~SServer()
{
}
