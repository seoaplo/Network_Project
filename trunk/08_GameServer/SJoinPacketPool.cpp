#include "SJoinPacketPool.h"


void	SJoinPacketPool::Push(SPacket pack)
{
	SScopeRock_Mutex ScopeLock(Mutex);

	m_PacketPool.push(pack);
}
SPacket	SJoinPacketPool::Pop()
{
	SScopeRock_Mutex ScopeLock(Mutex);

	SPacket RetPakcet = m_PacketPool.front();
	m_PacketPool.pop();
	return RetPakcet;
}

bool SJoinPacketPool::Init()
{
	return true;
}

bool SJoinPacketPool::Release()
{
	SScopeRock_Mutex ScopeLock(Mutex);
	while (m_PacketPool.empty())
	{
		m_PacketPool.pop();
	}
	return true;
}


SJoinPacketPool::SJoinPacketPool()
{
}


SJoinPacketPool::~SJoinPacketPool()
{
}
