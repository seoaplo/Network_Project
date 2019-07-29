#include "SRecvPacketPool.h"



void	SRecvPacketPool::Push(PACKET pack)
{
	SScopeRock_Mutex ScopeLock(Mutex);

	m_PacketPool.push(pack);
}
PACKET	SRecvPacketPool::Pop()
{
	SScopeRock_Mutex ScopeLock(Mutex);

	PACKET RetPakcet = m_PacketPool.front();
	m_PacketPool.pop();
	return RetPakcet;
}

bool SRecvPacketPool::Init()
{
	return true;
}

bool SRecvPacketPool::Release()
{
	SScopeRock_Mutex ScopeLock(Mutex);
	while (m_PacketPool.empty())
	{
		m_PacketPool.pop();
	}
	return true;
}

SRecvPacketPool::SRecvPacketPool()
{
}


SRecvPacketPool::~SRecvPacketPool()
{
}
