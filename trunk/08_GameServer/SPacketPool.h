#pragma once
#include "SServerStd.h"
#include "Protocol.h"
#include "Client/STemplate.h"
#include "Lock.h"

class SPacketPool : public Singleton<SPacketPool>
{
	friend class Singleton<SPacketPool>;
public:
	std::queue<SPacket> m_PacketPool;
	SmartMutex Mutex;
public:
	bool Init();
	bool Release();
public:
	void		Push(SPacket pack);
	SPacket		Pop();
	SPacket&	CheckPackcet()
	{
		return m_PacketPool.front();
	}
	bool	Empty()
	{
		if(m_PacketPool.empty())	return true;
		else						return false;
	}
	int GetSize()
	{
		SScopeRock_Mutex ScopeLock(Mutex);
		return m_PacketPool.size();
	}
private:
	SPacketPool();
public:
	~SPacketPool();
};

#define I_PacketPool SPacketPool::GetInstance()
