#pragma once
#include "SssBitMap.h"

class SssBitMapManeger
{
private:
	std::map<UINT, SssBitMap*> BitMapList;
	HDC MyScreenHDC;
	HINSTANCE MyHinstance;
	UINT iSize;
public:
	static SssBitMapManeger& GetInstance()
	{
		static SssBitMapManeger SingleBitmapManeger;
		return SingleBitmapManeger;
	}
public:
	UINT Load(const TCHAR* RouteString);
	bool CreateManeger(HDC TargetHDC, HINSTANCE TargetHinstance);
	SssBitMap* GetBitMap(UINT iKey);
public:
	bool Release();
private:
	SssBitMapManeger();
	~SssBitMapManeger();
};

#define BitMapManeger SssBitMapManeger::GetInstance()