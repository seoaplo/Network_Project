#pragma once
#include "SThread.h"
#include "SJoinPacketPool.h"

class SJoinThread : public SThread
{

public:
	bool Init();
	bool Frame();
	bool Release();
public:
	SJoinThread();
	~SJoinThread();
};

