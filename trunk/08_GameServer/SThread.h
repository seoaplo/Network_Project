#pragma once
#include "SServerStd.h"
#include "Protocol.h"
#include "SUserPool.h"
//#include "Game/sssstd.h"

class SThread
{
public:
	DWORD	m_iThreadID;
	HANDLE	m_hThread;

public:
	virtual bool Init() { return true; }; 
	virtual bool Frame() { return true; };
	virtual bool Release() { return true; };
public:
	SThread();
	~SThread();
};

