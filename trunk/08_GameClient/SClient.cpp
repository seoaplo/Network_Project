#include "SClient.h"

bool SClient::Init()
{

	WSAStartup(MAKEWORD(2, 2), &m_wsa);
	m_PakcetThread.Init();
	return true;
}
bool SClient::Frame()
{
	if (m_PakcetThread.Frame() == false) return false;
	return true;
}
bool SClient::Release()
{
	m_PakcetThread.Release();
	closesocket(m_listensock);
	WSACleanup();
	return true;
}

SClient::SClient()
{
}


SClient::~SClient()
{
}
