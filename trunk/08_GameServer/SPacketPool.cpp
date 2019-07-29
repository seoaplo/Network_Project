#include "SPacketPool.h"

void	SPacketPool::Push(SPacket pack)
{	
	SScopeRock_Mutex ScopeLock(Mutex);

	m_PacketPool.push(pack);
}
SPacket	SPacketPool::Pop()
{
	SScopeRock_Mutex ScopeLock(Mutex);

	SPacket RetPakcet = m_PacketPool.front();
	m_PacketPool.pop();
	return RetPakcet;
}

bool SPacketPool::Init()
{
	return true;
}

bool SPacketPool::Release()
{
	SScopeRock_Mutex ScopeLock(Mutex);
	while (m_PacketPool.empty())
	{
		m_PacketPool.pop();
	}
	return true;
}

SPacketPool::SPacketPool()
{
}


SPacketPool::~SPacketPool()
{
}
