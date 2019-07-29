#pragma once
#include "SThread.h"
#include "SUserPool.h"
#include "SJoinPacketPool.h"
#include "SGamePacketPool.h"

class SPacketThread : public SThread
{
public:
	SOCKET m_listensock;
	FD_SET  m_rSet;
	FD_SET  m_wSet;
	int m_addlen;

public:
	bool Init();
	bool Frame();
	bool Release();
public:
	bool PacketProcess();
	bool BroadCast() ;
	bool TargetSend();
public:
	SPacketThread();
	~SPacketThread();
};

