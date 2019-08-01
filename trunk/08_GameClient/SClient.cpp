#include "SClient.h"

bool SClient::Init()
{

	WSAStartup(MAKEWORD(2, 2), &m_wsa);
	m_PakcetThread.Init();
	while (SPacketThread::g_bProcessSuccecss == false);
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
	WaitForSingleObject(SPacketThread::g_hThread, INFINITE);
	while (I_RecvPacketPool.Empty() == false) I_RecvPacketPool.Pop();
	while (I_SendPacketPool.Empty() == false) I_SendPacketPool.Pop();
	WSACleanup();
	return true;
}

SClient::SClient()
{
}


SClient::~SClient()
{
}
