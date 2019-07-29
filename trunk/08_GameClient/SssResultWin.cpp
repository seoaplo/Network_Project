#include "SssResultWin.h"


bool SssResultWin::Init(HDC WindowDC, HDC OffScreen)
{
	MyWindowDC = WindowDC;
	MyOffScreenDC = OffScreen;
	iChangeSceen = -1;

	RECT rect;
	rect.left = 160;
	rect.top = 160;
	rect.right = 267 + 160;
	rect.bottom = 97 + 160;

	UINT Key = SingleImegeManeger.CreateImege(rect, L"../../../data/Warnning.bmp", WindowDC);
	MyBackGroundImege = SingleImegeManeger.GetImege(Key);

	MaxTime = 10.0f;
	Time = 0.0f;

	return true;
}
bool SssResultWin::Frame()
{
	Time += GetSecPerFrame;
	if (Time >= MaxTime)
	{
		iChangeSceen = SC_TITLE;
	}
	return true;
}
bool SssResultWin::Render()
{
	COLORREF Color = RGB(29, 112, 189);
	POINT Point;
	Point.x = 500;
	Point.y = 300;
	MyBackGroundImege->TransDraw(MyOffScreenDC, Point, 3, Color, IDO_RECT);
	return true;
}
bool SssResultWin::Release()
{
	Time = 0;
	return true;
}



SssResultWin::SssResultWin()
{
}


SssResultWin::~SssResultWin()
{
}
