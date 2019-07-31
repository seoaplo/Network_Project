#include "SssWall.h"

bool SssGround::PacketProcess(PACKET pack)
{
	switch (pack.Header.type)
	{
	case PACKET_GROUND_SET:
		{
			GROUND_STATE GroundState;
			memcpy(&GroundState, pack.msg, sizeof(GROUND_STATE));

			MyPos = GroundState.GroundPoint;
			MyCollider->SetPoint(MyPos);
		}
	}
	return true;
}

bool SssGround::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC)
{
	MyOffScreen = OffScreen;
	MyPos = TargetPos;

	ObjectName = L"GroundObject";

	MyRect;
	MyRect.left = 0;
	MyRect.top = 0;
	MyRect.right = 512;
	MyRect.bottom = 64;
	UINT Key = SingleImegeManeger.CreateImege(MyRect, L"../../../data/Wall2.bmp", WindowDC);
	MyImege = SingleImegeManeger.GetImege(Key);

	MyCollider = &CollisionManeger.AddCollider(MyPos, MyRect, this, Col_Rect);

	return true;
}
bool SssGround::Frame()
{
	
	return true;
}
bool SssGround::Render()
{
	MyImege->Draw(MyOffScreen, MyPos, 1, SRCCOPY);
	return true;
}
bool SssGround::Release()
{

	CollisionManeger.DeleteColider(MyCollider);
	DeleteObject(SelectObject(MyScreen, MyOldBitMap));
	DeleteDC(MyScreen);
	return true;
}
bool SssGround::CheckEvent(SssObject& TargetObject)
{
	return true;
}

SssGround::SssGround()
{
}


SssGround::~SssGround()
{
}

bool SssWall::PacketProcess(PACKET pack)
{
	switch (pack.Header.type)
	{
		case PACKET_WALL_SET:
		{
			WALL_STATE WallState;
			memcpy(&WallState, pack.msg, sizeof(WALL_STATE));

			MyPos = WallState.WallPoint;
			MyCollider->SetPoint(MyPos);
		}
	}
	return true;
}

bool SssWall::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC)
{
	MyOffScreen = OffScreen;
	MyPos = TargetPos;

	ObjectName = L"WallObject";

	MyRect;
	MyRect.left = 0;
	MyRect.top = 0;
	MyRect.right = 32;
	MyRect.bottom = 384;
	UINT Key = SingleImegeManeger.CreateImege(MyRect, L"../../../data/Wall1.bmp", WindowDC);
	MyImege = SingleImegeManeger.GetImege(Key);

	MyCollider = &CollisionManeger.AddCollider(MyPos, MyRect, this, Col_Rect);

	return true;
}
bool SssWall::Frame()
{

	return true;
}
bool SssWall::Render()
{
	MyImege->Draw(MyOffScreen, MyPos, 1, SRCCOPY);
	return true;
}
bool SssWall::Release()
{

	CollisionManeger.DeleteColider(MyCollider);
	DeleteObject(SelectObject(MyScreen, MyOldBitMap));
	DeleteDC(MyScreen);
	return true;
}
bool SssWall::CheckEvent(SssObject& TargetObject)
{
	return true;
}
SssWall::SssWall()
{
}


SssWall::~SssWall()
{
}