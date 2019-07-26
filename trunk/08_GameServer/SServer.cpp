#include "SServer.h"

bool SServer::Init()
{
	
	WSAStartup(MAKEWORD(2, 2), &m_wsa);
	m_listensock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN addr;
	ZeroMemory(&addr, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(10000);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int ret = bind(m_listensock, (SOCKADDR*)&addr, sizeof(addr));
	if (ret == SOCKET_ERROR)
	{
		E_MSG("bind");
		return;
	}

	ret = listen(m_listensock, SOMAXCONN);
	if (ret == SOCKET_ERROR)
	{
		E_MSG("listen");
		return;
	}
	printf("Sever Staaaaaaaaaaaaaaaaaaaaaaaaaart!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

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
		if (Frame()) break;
	}

	return Release();
}

SServer::SServer()
{
}


SServer::~SServer()
{
}
