#pragma once
#include "SServerStd.h"
#include "Protocol.h"
#include "Client/STemplate.h"
#include "Lock.h"

class SRecvPacketPool : public Singleton<SRecvPacketPool>
{
	friend class Singleton<SRecvPacketPool>;
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
	SRecvPacketPool();
public:
	~SRecvPacketPool();
};

#define I_RecvPacketPool SRecvPacketPool::GetInstance()
