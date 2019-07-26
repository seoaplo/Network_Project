#pragma once
#include "Game/sssstd.h"

class SssFSM
{
public:
	std::multimap<DWORD, std::multimap<DWORD, DWORD>> StateList;
public:
	void CreateFSM(DWORD iState, DWORD iEvent, DWORD iChangeState);
	DWORD GetState(DWORD iState, DWORD iEvent);
public:
	SssFSM();
	~SssFSM();
};

