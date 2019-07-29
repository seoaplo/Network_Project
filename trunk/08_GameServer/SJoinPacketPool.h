#pragma once
#include "SServerStd.h"
#include "Protocol.h"
#include "Client/STemplate.h"
#include "Lock.h"

class SJoinPacketPool : public Singleton<SJoinPacketPool>
{
	friend class Singleton<SJoinPacketPool>;
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
		if (m_PacketPool.empty())	return true;
		else						return false;
	}
private:
	SJoinPacketPool();
public:
	~SJoinPacketPool();
};

#define I_JoinPacketPool SJoinPacketPool::GetInstance()
