#pragma once
#include "SssStd.h"
#include "SssBitMapManeger.h"

class SssImege
{
private:
	UINT iMyKey;
	std::wstring MyRouteString;
	SssBitMap* MyBitMap;

	HDC  WindowDC;
	HDC MyRotateDC;
	HDC	RotateDrawDC;

	UINT RealDrawPosX;
	UINT RealDrawPosY;

	RECT MySizeRect;
	RECT MyScaleRect;

	float MyLength;

public:
	bool Create(RECT SizeRect, TCHAR* BitMapRouteString, HDC MyWindowDC);
	bool Draw(HDC TargetHDC, POINT TargetPos, float fScale, int iCopyOption, int DrawOption = 0);
	bool RotateDraw(HDC TargetHDC, POINT TargetPos, float fRotate, int iCopyOption, float fScaleX, float fScaleY);
	bool TransDraw(HDC TargetHDC, POINT TargetPos, float fScale, COLORREF TargetColor, int iDrawOption = 0);
	bool TransRotateDraw(HDC TargetHDC, POINT TargetPos, float fRotate, COLORREF TargetColor, float fScaleX, float fScaleY);
	bool BlendDrawer(HDC OffScreen, HDC DrawDC, RECT TargetRect, float fAlpha);
	bool Release();
public:
	bool operator==(const RECT TargetRect);
	bool operator!=(const RECT TargetRect);
	bool operator==(const TCHAR* TargetString);
	bool operator!=(const TCHAR* TargetString);
public:
	SssImege();
	~SssImege();
};

enum ImegeDrawOption
{
	IDO_Default,
	IDO_Width,
	IDO_Height,
	IDO_RECT,
	IDO_WidthMirror,
	IDO_HeightMirror,
	IDO_RECTMirror
};