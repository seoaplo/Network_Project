#pragma once
#include "SceenList.h"
class SssSceenManeger
{
public:
	std::map<DWORD, SssSceeen*> MySceenList;
	HDC MyOffScreen;
	HDC MyWindowScreen;
	HDC MyBlendScreen;
	HBITMAP MyBlendBitMap;
	HBITMAP MyOldBitMap;
	bool bChange;
	float ChangeSceenTime;
	float ChangeSceenMaxTime;
	float fAlpha;
	SssSceeen* MyOldSceen;
	SssSceeen* MySceen;
public:
	static SssSceenManeger& GetInstance()
	{
		static SssSceenManeger SingleSceenManeger;
		return SingleSceenManeger;
	}
	bool Init(HDC TargetOffScreenDC, HDC TargetWindowDC);
	bool Frame();
	bool Render();
	bool Release();
	bool ChangeSceen(int iState);
private:
	SssSceenManeger() {};
	~SssSceenManeger() {};
};

#define SingleSceenManeger SssSceenManeger::GetInstance()

