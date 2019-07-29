#pragma once
#include "Game/Ssslibheader.h"

class SssEffect : public SssObject
{
public:
	float MaxLifeSecond;
	struct DrawData
	{
		POINT MyPos;
		float LifeTime;
		float Scale;
		bool bSoundStart;
		int DrawOption;
		SssSprite MySprite;
	};
	std::list<DrawData*> DrawList;
public:
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, const TCHAR* RouteString, const TCHAR* RectString,
		COLORREF COLOR, const TCHAR* RectRouteString, const char* SoundString, float LifeSecond);
	bool Frame();
	bool Render();
	bool Release();
	void SetDrawData(POINT TargetPos, float TargetScale, int TargetDrawOption);
public:
	SssEffect();
	~SssEffect();
};

