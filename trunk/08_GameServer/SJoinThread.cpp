#include "SJoinThread.h"

DWORD WINAPI JoinThread(LPVOID arg)
{
	while (I_JoinPacketPool.Empty() == false)
	{
		SPacket UserPacket;
		UserPacket = I_PacketPool.Pop();

		switch (UserPacket.pack.Header.type)
		{
		default:
			E_MSG("알 수 없는 패킷 - JoinPacket");
			break;
		}
	}
	return 1;
}

bool SJoinThread::Init()
{
	m_hThread = CreateThread(0, 0, JoinThread, 0, 0, &m_iThreadID);
	return true;
}
bool SJoinThread::Frame()
{	
	
	return true;
}
bool SJoinThread::Release()
{
	CloseHandle(m_hThread);
	return true;
}


SJoinThread::SJoinThread()
{
}


SJoinThread::~SJoinThread()
{
}
