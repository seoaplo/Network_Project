#pragma once
#include "Ssslibheader.h"
class SssTitleObject : public SssObject
{
public:
	bool bCheckMouse;
	COLORREF MyColor;
	bool bTrans;
	bool bInside;
	float MyfScale;
	RECT MyRect;
	bool bChangeSceen;
public:
	virtual bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, char* SoundStirng, RECT TargetRect,
		TCHAR* RouteString, TCHAR* RectString, TCHAR* RectRouteString, COLORREF TargetColor, bool Check, float fScale);
	virtual bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, char* SoundStirng, RECT TargetRect,
		TCHAR* RouteString, TCHAR* RectString, TCHAR* RectRouteString, TCHAR* MaskRouteString, bool Check, float fScale);
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	bool GetChangeSceen()
	{
		return bChangeSceen;
	}
public:
	SssTitleObject();
	~SssTitleObject();
};

class SssStartObject : public SssTitleObject
{
public:
	bool bCheckMouse;
	COLORREF MyColor;
	bool bTrans;
	bool bInside;
	float MyfScale;
	RECT MyRect;
public:
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, char* SoundStirng, RECT TargetRect,
		TCHAR* RouteString, TCHAR* RectString, TCHAR* RectRouteString, COLORREF TargetColor, bool Check, float fScale);
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, char* SoundStirng, RECT TargetRect,
		TCHAR* RouteString, TCHAR* RectString, TCHAR* RectRouteString, TCHAR* MaskRouteString, bool Check, float fScale);
	bool Frame();
	bool Render();
	bool Release();
public:
	SssStartObject() {};
	~SssStartObject() {};
};

class SssExitObject : public SssTitleObject
{
public:
	bool bCheckMouse;
	COLORREF MyColor;
	bool bTrans;
	bool bInside;
	float MyfScale;
	RECT MyRect;
public:
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, char* SoundStirng, RECT TargetRect,
		TCHAR* RouteString, TCHAR* RectString, TCHAR* RectRouteString, COLORREF TargetColor, bool Check, float fScale);
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, char* SoundStirng, RECT TargetRect,
		TCHAR* RouteString, TCHAR* RectString, TCHAR* RectRouteString, TCHAR* MaskRouteString, bool Check, float fScale);
	bool Frame();
	bool Render();
	bool Release();
public:
	SssExitObject() {};
	~SssExitObject() {};
};
