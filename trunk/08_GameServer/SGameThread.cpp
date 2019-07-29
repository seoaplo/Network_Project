#include "SGameThread.h"

DWORD WINAPI GameThread(LPVOID arg)
{
	while (1)
	{
		
	}
	return 1;
}

bool SGameThread::Init()
{
	m_hThread = CreateThread(0, 0, GameThread, 0, 0, &m_iThreadID);
	return true;
}
bool SGameThread::Frame()
{
	return true;
}
bool SGameThread::Release()
{
	CloseHandle(m_hThread);
	return true;
}

SGameThread::SGameThread()
{
}


SGameThread::~SGameThread()
{
}
