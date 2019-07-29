#pragma once
#include "SUser.h"
#include "Client/STemplate.h"
#include "Lock.h"
#define USER_MAXSIZE 10

class SUserPool : public Singleton<SUserPool>
{
	friend class Singleton<SUserPool>;
public:
	int m_iUserMax;
	SmartMutex Mutex;
	std::vector<SUser> m_UserPool;
public:
	int		PushUser(SOCKET sock);
	bool	DeleteUser(int iUserNum);
public:
	SUser& GetUser(int iUserNum)
	{
		SScopeRock_Mutex ScopeLock(Mutex);
		return m_UserPool[iUserNum];
	}
public:
	bool Init();
	bool Frame();
	bool Release();
public:
	std::vector<SUser>& GetUserPool()
	{
		return m_UserPool;
	}
private:
	SUserPool();
public:
	~SUserPool();
};

#define I_UserPool SUserPool::GetInstance()
