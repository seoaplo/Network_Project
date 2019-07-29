#include "SGamePacketPool.h"


void	SGamePacketPool::Push(SPacket pack)
{
	SScopeRock_Mutex ScopeLock(Mutex);

	m_PacketPool.push(pack);
}
SPacket	SGamePacketPool::Pop()
{
	SScopeRock_Mutex ScopeLock(Mutex);

	SPacket RetPakcet = m_PacketPool.front();
	m_PacketPool.pop();
	return RetPakcet;
}

bool SGamePacketPool::Init()
{
	return true;
}

bool SGamePacketPool::Release()
{
	SScopeRock_Mutex ScopeLock(Mutex);
	while (m_PacketPool.empty())
	{
		m_PacketPool.pop();
	}
	return true;
}


SGamePacketPool::SGamePacketPool()
{
}


SGamePacketPool::~SGamePacketPool()
{
}
