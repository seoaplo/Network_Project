#include "SssBullet.h"

bool SssBullet::PacketProcess(PACKET pack)
{
	return true;
}

bool SssBullet::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, float fSpeed, SssPoint Distans, SssPoint RealPos , float TargetDgree)
{
	return true;
}
bool SssBullet::Frame()
{
	return true;
}
bool SssBullet::Render()
{
	return true;
}
bool SssBullet::Release()
{
	return true;
}
bool SssBullet::CheckEvent(SssObject& TargetObject)
{
	return true;
}
SssBullet::SssBullet()
{
	
}
SssBullet::~SssBullet()
{
}


bool SssPlayerBullet::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC,
	float fSpeed, SssPoint Distans, SssPoint RealPos, float TargetDgree)
{
	MyOffScreen = OffScreen;
	MyPos.x = TargetPos.x;
	MyPos.y = TargetPos.y;

	MyDegree = TargetDgree;

	MyRealPos = RealPos;
	MyDistance = Distans;
	MyfSpeed = fSpeed;

	RECT rect;
	rect.left = 496;
	rect.right = 116;
	rect.top = 27;
	rect.bottom = 18;
	bDelete = false;
	COLORREF Color = RGB(29, 112, 189);
	MyCollider = &CollisionManeger.AddCollider(MyPos, rect, this, Col_Point);
	int Key = SingleSpriteManeger.CreateSprite
	(L"../../../data/PlayerEffect2.txt", L"../../../data/PlayerAttack1.bmp", L"RectPlayerBullet", Color, WindowDC, 1.5);
	SpriteImege = SingleSpriteManeger.GetSprite(Key);


	SssEffectTime = 0.0f;
	SssEffectMaxTime = 0.1f;
	MyEffect.Init(OffScreen, MyPos, WindowDC, L"../../../data/PlayerAttack1.bmp", L"RectBulletLanding",
		Color, L"../../../data/PlayerEffect2.txt", "../../../data/BulletLanding.wav", SssEffectMaxTime);
	bDeleteReady = false;
	
	ObjectName = L"Player_Bullet";



	return true;
}
bool SssPlayerBullet::Frame()
{
	MyEffect.Frame();
	if (!bDeleteReady)
	{
		MyRealPos.x += min(MyDistance.x * MyfSpeed * GetSecPerFrame, MyfSpeed);
		MyRealPos.y += min(MyDistance.y * MyfSpeed * GetSecPerFrame, MyfSpeed);
		MyPos.x = (int)MyRealPos.x;
		MyPos.y = (int)MyRealPos.y;
		MyCollider->SetPoint(MyPos);
		SpriteImege->Frame();
		if (MyPos.x < 0 || MyPos.x > 2048 || MyPos.y < 0 || MyPos.y > 768)
		{
			bDelete = true;
		}
	}
	else if (SssEffectMaxTime > SssEffectTime)
	{
		SssEffectTime += GetSecPerFrame;
	}
	else
	{
		bDelete = true;
	}
	
	return true;
}
bool SssPlayerBullet::Render()
{
	if (!bDeleteReady)
	{
		SpriteImege->RotateDraw(MyOffScreen, MyPos, MyDegree, 1, 1);
	}
	MyEffect.Render();
	return true;
}
bool SssPlayerBullet::Release()
{
	CollisionManeger.DeleteColider(MyCollider);
	MyEffect.Release();
	return true;
}
bool SssPlayerBullet::CheckEvent(SssObject& TargetObject)
{
	if (TargetObject.GetName() == L"MainBossObject")
	{
		if (!bDeleteReady)
		{
			MyEffect.SetDrawData(MyPos, 2, IDO_RECT);
			bDeleteReady = true;
		}
	}

	return true;
}



bool SssSubBoss1Bullet::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC,
	float fSpeed, SssPoint Distans, SssPoint RealPos, float TargetDgree)
{
	MyOffScreen = OffScreen;
	MyPos.x = TargetPos.x;
	MyPos.y = TargetPos.y;

	MyDegree = TargetDgree;

	MyRealPos = RealPos;
	MyDistance = Distans;
	MyfSpeed = fSpeed;

	RECT rect;
	rect.left = 0;
	rect.right = 0;
	rect.top = 60;
	rect.bottom = 60;
	bDelete = false;
	COLORREF Color = RGB(29, 112, 189);
	MyCollider = &CollisionManeger.AddCollider(MyPos, rect, this, Col_Rect);
	int Key = SingleSpriteManeger.CreateSprite
	(L"../../../data/PlayerEffect1.txt", L"../../../data/Player_Effect.bmp", L"RectMeteo", Color, WindowDC, 1.5);
	SpriteImege = SingleSpriteManeger.GetSprite(Key);


	SssEffectTime = 0.0f;
	SssEffectMaxTime = 0.1f;
	MyEffect.Init(OffScreen, MyPos, WindowDC, L"../../../data/Player_Effect.bmp", L"RectEffectBoom",
		Color, L"../../../data/PlayerEffect1.txt", "../../../data/Boom.wav", SssEffectMaxTime);
	bDeleteReady = false;

	ObjectName = L"Boss_Bullet";

	return true;
}
bool SssSubBoss1Bullet::Frame()
{
	MyEffect.Frame();
	if (!bDeleteReady)
	{
		MyRealPos.x += min(MyDistance.x * MyfSpeed * GetSecPerFrame, MyfSpeed);
		MyRealPos.y += min(MyDistance.y * MyfSpeed * GetSecPerFrame, MyfSpeed);
		MyPos.x = (int)MyRealPos.x;
		MyPos.y = (int)MyRealPos.y;
		MyCollider->SetPoint(MyPos);
		SpriteImege->Frame();
		if (MyPos.x < 0 || MyPos.x > 2048 || MyPos.y < 0 || MyPos.y > 768)
		{
			bDelete = true;
		}
	}
	else if (SssEffectMaxTime > SssEffectTime)
	{
		SssEffectTime += GetSecPerFrame;
	}
	else
	{
		bDelete = true;
	}

	return true;
}
bool SssSubBoss1Bullet::Render()
{
	if (!bDeleteReady)
	{
		SpriteImege->RotateDraw(MyOffScreen, MyPos, MyDegree, 1, 1);
	}
	MyEffect.Render();
	return true;
}
bool SssSubBoss1Bullet::Release()
{
	CollisionManeger.DeleteColider(MyCollider);
	MyEffect.Release();
	return true;
}
bool SssSubBoss1Bullet::CheckEvent(SssObject& TargetObject)
{
	if (!bDeleteReady)
	{
		if (TargetObject.GetName() == L"GroundObject" || TargetObject.GetName() == L"WallObject" ||
			TargetObject.GetName() == L"PlayerObject")
		{
			MyEffect.SetDrawData(MyPos, 2, IDO_RECT);
			bDeleteReady = true;
		}
	}

	return true;
}
