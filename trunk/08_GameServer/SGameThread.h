#pragma once
#include "SThread.h"
#include "SGamePacketPool.h"
#include "SssStage.h"

class SGameThread : public SThread
{
public:
	bool Init();
	bool Frame();
	bool Release();
public:
	SGameThread();
	~SGameThread();
};

