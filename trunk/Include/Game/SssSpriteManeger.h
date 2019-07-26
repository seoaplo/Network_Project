#pragma once
#include "SssSprite.h"

struct LoadSpriteData
{
	std::vector<RECT> Rect;
	TCHAR RectName[100];
	int loopframe;
	int framesize;
};

class SssSpriteManeger
{
public:
	std::map<int, SssSprite*> MySpriteList;
	int iSize;
public:
	int CreateSprite(TCHAR* RectRouteString, TCHAR* ImegeRouteString, TCHAR* MaskRouteString, TCHAR*  SpriteName, HDC TargetWindowDC, float PlayTime, int loopframe = 0);
	int CreateSprite(TCHAR* RectRouteString,  TCHAR* TransRouteString, TCHAR*  SpriteName, COLORREF Color, HDC TargetWindowDC, float PlayTime, int loopframe = 0);
	std::vector<LoadSpriteData>* LoadRectFile(TCHAR* RouteString);
	SssSprite* GetSprite(int Key);
	int GetKey(TCHAR* SpriteName);
	bool Release();
	static SssSpriteManeger& GetInstance()
	{
		static SssSpriteManeger SingleManeger;
		return SingleManeger;
	}
private:
	SssSpriteManeger();
	~SssSpriteManeger();
};



#define SingleSpriteManeger SssSpriteManeger::GetInstance()