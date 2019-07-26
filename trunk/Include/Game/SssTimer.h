#pragma once
#include "SssStd.h"

class SssTimer
{
private:
	TCHAR lpszDebugPrint[MAX_PATH];
	int			iFPS;
	float		fSecondPerFrame;
	float		fPlaySecond;
	float		fCheckSecond;
	DWORD		dwBeforeFPS;
	DWORD		dwFrameCnt;
public:
	int			 GetFPS()
	{
		return iFPS;
	}
	float		 GetSecondPreFrame()
	{
		return fSecondPerFrame;
	}
	float		 GetPlaySecond()
	{
		return fPlaySecond;
	}
	TCHAR& GetDeBugPrint()
	{
		return	*lpszDebugPrint;
	}
	static SssTimer& GetInstance()
	{
		static SssTimer SingleTimer;
		return SingleTimer;
	}
public:
	bool Init();
	bool Frame();
	bool Renderer();
	bool Release();
private:
	SssTimer();
	~SssTimer();
};

#define SingleTimer SssTimer::GetInstance()
#define GetSecPerFrame SingleTimer.GetSecondPreFrame()