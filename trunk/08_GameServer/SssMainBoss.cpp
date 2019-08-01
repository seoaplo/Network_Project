#include "SssMainBoss.h"

bool SssMainBoss::PacketProcess(PACKET pack)
{
	switch (pack.Header.type)
	{
		case PACKET_BOSS_SET:
		{
			BOSS_STATE BossState;
			memcpy(&BossState, pack.msg, sizeof(BOSS_STATE));

			MyPos = BossState.BossPoint;
			MyState = BossState.BossState;
			MybeforeState = BossState.BossState;
		}
	}
	return true;
}

bool SssMainBoss::Init(HDC OffScreen, POINT TargetPos, HDC WindowDC)
{
	MyOffScreen = OffScreen;
	MyScreen = CreateCompatibleDC(WindowDC);
	MyBitMap = CreateCompatibleBitmap(WindowDC, 500, 500);
	MyOldBitMap = (HBITMAP)SelectObject(MyScreen, MyBitMap);

	MyPos = TargetPos;
	MyRect.left = 0;
	MyRect.top = 0;
	MyRect.right = 57;
	MyRect.bottom = 190;

	MyCollider = &CollisionManeger.AddCollider(MyPos, MyRect, this, Col_Rect);
	ObjectName = L"MainBossObject";

	for (int iFirstCount = 0; iFirstCount < Boss_StateSize; iFirstCount++)
	{
		for (int iSecondCount = 0; iSecondCount < Boss_EventSize; iSecondCount++)
		{
			MyFsm.CreateFSM(iFirstCount, iSecondCount, iSecondCount);
		}
	}
	srand(time(NULL));

	MyColor = RGB(255, 0, 255);

	bStart = true;
	MyStartTime = 0.0f;
	MyStartMaxTime = 2.0f;

	bIdle = false;
	MyIdleTime = 0.0f;
	MyidleMaxTime = 1.0f;

	bTeleport1 = false;
	MyTeleportTime1 = 0.0f;
	MyTeleportMaxTime1 = 1.0f;

	bStop = false;
	MyStopTime = 0.0f;
	MyStopMaxTime = 3.0f;

	bTeleport2 = false;
	MyTeleportTime2 = 0.0f;
	MyTeleportMaxTime2 = 1.0f;

	DamegeTime = 0.0f;
	DamegeMaxTime = 0.1f;

	int SpriteNumber = SingleSpriteManeger.CreateSprite
	(L"../../../data/BossRect.txt", L"../../../data/MainBoss.bmp", L"BossIdle", MyColor, WindowDC, MyidleMaxTime);
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	MyStateList.insert(std::make_pair(Boss_Idle, MySprite));
	MySprite->Init();

	SpriteNumber = SingleSpriteManeger.GetKey(L"BossSpawn");
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	MySprite->SetDrawTime(MyStartMaxTime);
	MyStateList.insert(std::make_pair(Boss_Spawn, MySprite));
	MySprite->Init();

	SpriteNumber = SingleSpriteManeger.GetKey(L"BossTeleport1");
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	MySprite->SetDrawTime(MyTeleportMaxTime1);
	MyStateList.insert(std::make_pair(Boss_Teleport1, MySprite));
	MySprite->Init();

	SpriteNumber = SingleSpriteManeger.GetKey(L"BossTeleport2");
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	MySprite->SetDrawTime(MyTeleportMaxTime2);
	MyStateList.insert(std::make_pair(Boss_Teleport2, MySprite));
	MySprite->Init();

	MyState = Boss_Spawn;
	MySprite = MyStateList.find(MyState)->second;

	MyHP = 100;
	
	return true;
}
bool SssMainBoss::Frame()
{
	
	if (bReady)
	{
		return true;
	}
	if (bIdle && MyIdleTime < MyidleMaxTime )
	{
		MyIdleTime += GetSecPerFrame;
		MyState = MyFsm.GetState(MyState, Boss_Idle);
	}
	else if(bIdle)
	{
		MyIdleTime = 0;
		bIdle = false;
		bTeleport1 = true;
	}

	if (bTeleport1 && MyTeleportTime1 < MyTeleportMaxTime1)
	{
		MyTeleportTime1 += GetSecPerFrame;
		MyState = MyFsm.GetState(MyState, Boss_Teleport1);
	}
	else if (bTeleport1)
	{
		bTeleport1 = false;
		MyTeleportTime1 = 0;
		MyPos.x = -500;
		MyPos.y = -500;
		bStop = true;
	}

	if (bStop && MyStopTime < MyStopMaxTime)
	{
		MyStopTime += GetSecPerFrame;	
	}
	else if(bStop)
	{
		bStop = false;
		MyStopTime = 0;
		int Xpos = (MyPlayer->GetPos().x - 200) + (rand() % 400);
		int Ypos = (MyPlayer->GetPos().y - 200) + (rand() % 400);
		MyPos.x = Xpos;
		MyPos.y = Ypos;
		bTeleport2 = true;
	}

	if (bTeleport2 && MyTeleportTime2 < MyTeleportMaxTime2)
	{
		MyTeleportTime2 += GetSecPerFrame;
		MyState = MyFsm.GetState(MyState, Boss_Teleport2);
	}
	else if(bTeleport2)
	{
		bTeleport2 = false;
		MyTeleportTime2 = 0;
		bIdle = true;
	}

	if (MyStartTime < MyStartMaxTime && bStart)
	{
		MyStartTime += GetSecPerFrame;
		MyState = MyFsm.GetState(MyState, Boss_Spawn);
	}
	else if(bStart)
	{
		bStart = false;
		bIdle = true;
	}

	if (MybeforeState != MyState)
	{
		MySprite->Init();
	}
	if (!bStop)
	{
		MySprite = MyStateList.find(MyState)->second;
		MySprite->Frame();
		MybeforeState = MyState;
	}
	DamegeTime += GetSecPerFrame;
	MyCollider->SetPoint(MyPos);
	return true;
}
bool SssMainBoss::Render()
{
	if (bReady)
	{
		bReady = false;
		return true;
	}
	if (!bStop)
	{
		RECT CameraRect;
		CameraRect.left = MyPos.x - 250;
		CameraRect.top = MyPos.y - 250;
		CameraRect.right = MyPos.x + 250;
		CameraRect.bottom = MyPos.y + 250;
		POINT CameraPos;
		CameraPos.x = 250;
		CameraPos.y = 210;
		BitBlt(MyScreen, 0, 0, CameraRect.right, CameraRect.bottom,
			MyOffScreen, CameraRect.left, CameraRect.top, SRCCOPY);
		if (MyPlayer->GetPos().x > MyPos.x)
		{
			MySprite->Draw(MyScreen, CameraPos, 2, IDO_RECT);
		}
		else
		{
			MySprite->Draw(MyScreen, CameraPos, 2, IDO_WidthMirror);
		}
		BitBlt(MyOffScreen, CameraRect.left, CameraRect.top, CameraRect.right, CameraRect.bottom,
			MyScreen, 0, 0, SRCCOPY);
	}
	
	
	return true;
}
bool SssMainBoss::Release()
{
	MyStateList.clear();
	if (MyCollider != NULL)
	{
		CollisionManeger.DeleteColider(MyCollider);
		MyCollider = NULL;
	}
	DeleteObject(SelectObject(MyScreen, MyOldBitMap));
	DeleteDC(MyScreen);

	return true;
}
bool SssMainBoss::CheckEvent(SssObject& TargetObject)
{
	return true;
}


SssMainBoss::SssMainBoss()
{
}


SssMainBoss::~SssMainBoss()
{
}
