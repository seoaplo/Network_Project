#pragma once
#include "SServerStd.h"
#include "Protocol.h"
#include "Client/STemplate.h"
#include "Lock.h"

class SSendPacketPool : public Singleton<SSendPacketPool>
{
	friend class Singleton<SSendPacketPool>;
public:
	std::queue<PACKET> m_PacketPool;
	SmartMutex Mutex;
public:
	bool Init();
	bool Release();
public:
	void		Push(PACKET pack);
	PACKET		Pop();
	PACKET&	CheckPackcet()
	{
		return m_PacketPool.front();
	}
	bool	Empty()
	{
		if (m_PacketPool.empty())	return true;
		else						return false;
	}
private:
	SSendPacketPool();
public:
	~SSendPacketPool();
};

#define I_SendPacketPool SSendPacketPool::GetInstance()
