#include "SVictory.h"

bool SVictory::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC)
{
	MyOffScreen = OffScreen;
	MyScreen = CreateCompatibleDC(WindowDC);
	MyBitMap = CreateCompatibleBitmap(WindowDC, 500, 500);
	MyOldBitMap = (HBITMAP)SelectObject(MyScreen, MyBitMap);

	MyPos = TargetPos;
	MyRect.left = 0;
	MyRect.top = 0;
	MyRect.right = 88;
	MyRect.bottom = 88;

	MyCollider = &CollisionManeger.AddCollider(MyPos, MyRect, this, Col_Rect);
	ObjectName = L"VictoryObject";

	UINT iImege = SingleImegeManeger.CreateImege(MyRect, L"../../../data/Victory.bmp", WindowDC);
	MyImege = SingleImegeManeger.GetImege(iImege);

	return true;
}
bool SVictory::Frame()
{
	return true;
}
bool SVictory::Render()
{
	MyImege->Draw(MyOffScreen, MyPos, 1, SRCCOPY);
	return true;
}
bool SVictory::Release()
{
	CollisionManeger.DeleteColider(MyCollider);
	DeleteObject(SelectObject(MyScreen, MyOldBitMap));
	DeleteDC(MyScreen);
	return true;
}
bool SVictory::CheckEvent(SssObject& TargetObject)
{
	return true;
}
bool SVictory::PacketProcess(PACKET pack)
{
	return true;
}

SVictory::SVictory()
{
}


SVictory::~SVictory()
{
}
