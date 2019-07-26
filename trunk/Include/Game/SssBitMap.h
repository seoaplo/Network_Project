#pragma once
#include "SssStd.h"
class SssBitMap
{
private:
	HBITMAP MyBitMap;
	HDC		MyHDC;
	HBITMAP MyOldBitMap;
	std::wstring MyWideString;
	UINT		iMyIndex;
public:
	UINT& GetIndex()
	{
		return iMyIndex;
	}
	HBITMAP GetBitMap()
	{
		return MyBitMap;
	}
public:
	bool Load(HINSTANCE TargetHinstance, HDC TargetHDC, TCHAR* RouteTString, UINT TargetIndex);
	bool Draw(HDC TargetHDC, POINT TargetPos, RECT SizeRect, RECT ScaleRect, int iCopyOption);
	bool Draw(HDC TargetHDC, POINT TargetPos, RECT SizeRect, POINT ScalePoint, int iCopyOption);
	bool Draw(HDC TargetHDC, POINT TargetPos, RECT SizeRect, int iCopyOption);
	bool TransDraw(HDC TargetHDC, POINT TargetPos, RECT SizeRect, RECT ScaleRect, COLORREF TargetColor);
	bool Release();
public:
	bool operator==(const UINT Target)
	{
		return iMyIndex == Target ? true : false;
	}
	bool operator!=(const UINT Target)
	{
		return iMyIndex != Target ? true : false;
	}
	bool operator==(const TCHAR* TargetString)
	{
		return MyWideString == TargetString ? true : false;
	}
	bool operator!=(const TCHAR* TargetString)
	{
		return MyWideString == TargetString ? true : false;
	}
public:
	SssBitMap();
	~SssBitMap();
};

