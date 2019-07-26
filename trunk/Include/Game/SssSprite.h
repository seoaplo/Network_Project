#pragma once
#include "SssTimer.h"
#include "SssImegeManeger.h"

class SssSprite
{
public:
	std::wstring MyName;
	std::vector<SssImege*> Sprite;
	std::vector<SssImege*> SpriteMask;
	COLORREF MyColor;
	bool bTrans;
	float MyPlayTime;
	float DrawTime;
	float CheckTime;
	int loopIndex;
	int DrawIndex;
public:
	bool CreateSprite(std::vector<RECT>& TargetRectList, TCHAR* SpriteName, TCHAR* BasicRouteString, TCHAR* MaskRouteString, HDC TargetWindowDC, float PlayTime, int loopframe = 0);
	bool CreateSprite(std::vector<RECT>& TargetRectList, TCHAR* SpriteName,TCHAR* BasicRouteString, HDC TargetWindowDC, COLORREF TargetColor, float PlayTime, int loopframe = 0);
	bool Draw(HDC TargetHDC, POINT TargetPos, float fScale, int DrawOption = 0);
	bool RotateDraw(HDC TargetHDC, POINT TargetPos, float fRotate, float fScaleX, float fScaleY);
	void SetDrawTime(float TargetTime)
	{
		MyPlayTime = TargetTime;
		DrawTime = TargetTime / Sprite.size();
	}
public:
	bool Init();
	bool Frame();
	bool Release();
public:
	SssSprite& operator=(const SssSprite& TargetSprite);
	bool operator==(const TCHAR* TargetString)
	{
		return TargetString == MyName ? true : false;
	}
	bool operator!=(const TCHAR* TargetString)
	{
		return TargetString != MyName ? true : false;
	}
public:
	SssSprite();
	~SssSprite();
};

