#include "SSendPacketPool.h"


void	SSendPacketPool::Push(PACKET pack)
{
	SScopeRock_Mutex ScopeLock(Mutex);

	m_PacketPool.push(pack);
}
PACKET	SSendPacketPool::Pop()
{
	SScopeRock_Mutex ScopeLock(Mutex);

	PACKET RetPakcet = m_PacketPool.front();
	m_PacketPool.pop();
	return RetPakcet;
}

bool SSendPacketPool::Init()
{
	return true;
}

bool SSendPacketPool::Release()
{
	SScopeRock_Mutex ScopeLock(Mutex);
	while (m_PacketPool.empty())
	{
		m_PacketPool.pop();
	}
	return true;
}

SSendPacketPool::SSendPacketPool()
{
}


SSendPacketPool::~SSendPacketPool()
{
}
