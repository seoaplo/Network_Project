#pragma once
#include "SServerStd.h"
#include "Protocol.h"
#include "Client/STemplate.h"
#include "Lock.h"

class SGamePacketPool : public Singleton<SGamePacketPool>
{
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
	SGamePacketPool();
public:
	~SGamePacketPool();
};

#define I_GamePacketPool SGamePacketPool::GetInstance()
