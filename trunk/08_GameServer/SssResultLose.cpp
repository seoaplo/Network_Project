#include "SssResultLose.h"



bool SssResultLose::Init(HDC WindowDC, HDC OffScreen)
{
	MyWindowDC = WindowDC;
	MyOffScreenDC = OffScreen;
	iChangeSceen = -1;

	RECT rect;
	rect.left = 174;
	rect.top = 289;
	rect.right = 238 + 174;
	rect.bottom = 95 + 289;

	UINT Key = SingleImegeManeger.CreateImege(rect, L"../Data/Warnning.bmp", WindowDC);
	MyBackGroundImege = SingleImegeManeger.GetImege(Key);

	MaxTime = 10.0f;
	Time = 0.0f;

	return true;
}
bool SssResultLose::Frame()
{
	Time += GetSecPerFrame;
	if (Time >= MaxTime)
	{
		iChangeSceen = SC_TITLE;
	}
	return true;
}
bool SssResultLose::Render()
{
	COLORREF Color = RGB(29, 112, 189);
	POINT Point;
	Point.x = 500;
	Point.y = 300;
	MyBackGroundImege->TransDraw(MyOffScreenDC, Point, 3, Color, IDO_RECT);
	return true;
}
bool SssResultLose::Release()
{
	Time = 0;
	return true;
}

SssResultLose::SssResultLose()
{
}


SssResultLose::~SssResultLose()
{
}
