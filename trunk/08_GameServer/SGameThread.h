#pragma once
#include "SThread.h"
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

