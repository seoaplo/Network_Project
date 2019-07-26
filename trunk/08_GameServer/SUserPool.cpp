#include "SUserPool.h"


bool SUserPool::Init()
{
	SScopeRock_Mutex ScopeLock(Mutex);
	Release();
	m_UserPool.resize(USER_MAXSIZE);
	for (auto User : m_UserPool)
	{
		User.Init();
	}
	m_iUserMax = -1;
	return true;
}
bool SUserPool::Frame()
{
	return true;
}
bool SUserPool::Release()
{
	SScopeRock_Mutex ScopeLock(Mutex);
	for (auto User : m_UserPool)
	{
		User.Release();
	}
	m_UserPool.clear();
	return true;
}

int SUserPool::PushUser(SOCKET sock)
{
	SScopeRock_Mutex ScopeLock(Mutex);

	if(m_iUserMax <= USER_MAXSIZE) return -1;

	m_iUserMax++;
	int iCount = 0;
	for (auto User : m_UserPool)
	{
		if(User.m_bReady == false ) break;
		iCount++;
	}
	m_UserPool[iCount].m_sock = sock;
	return iCount;
}
bool SUserPool::DeleteUser(int iUserNum)
{
	SScopeRock_Mutex ScopeLock(Mutex);

	if(iUserNum < 0 || m_iUserMax < iUserNum) return false;

	m_UserPool[iUserNum].Release();
	m_iUserMax--;
	return true;
}


SUserPool::SUserPool()
{
}


SUserPool::~SUserPool()
{
}
