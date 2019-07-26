#include "SssMainBoss.h"



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

	bAttack = false;
	bSummon = false;
	bMagic = false;

	MySummonTime = 0.0f;
	MySummonMaxTime = 1.0f;

	MyMagicTime = 0.0f;
	MyMagicMaxTime = 1.0f;

	bTeleport1 = false;
	MyTeleportTime1 = 0.0f;
	MyTeleportMaxTime1 = 1.0f;

	bStop = false;
	MyStopTime = 0.0f;
	MyStopMaxTime = 6.0f;

	bTeleport2 = false;
	MyTeleportTime2 = 0.0f;
	MyTeleportMaxTime2 = 1.0f;

	DamegeTime = 0.0f;
	DamegeMaxTime = 0.1f;

	int SpriteNumber = SingleSpriteManeger.CreateSprite
	(L"../Data/BossRect.txt", L"../Data/MainBoss.bmp", L"BossIdle", MyColor, WindowDC, MyidleMaxTime);
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

	SpriteNumber = SingleSpriteManeger.GetKey(L"BossDeath");
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	MySprite->SetDrawTime(1);
	MyStateList.insert(std::make_pair(Boss_Death, MySprite));
	MySprite->Init();

	SpriteNumber = SingleSpriteManeger.GetKey(L"BossSummon");
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	MySprite->SetDrawTime(MySummonMaxTime);
	MyStateList.insert(std::make_pair(Boss_Summon, MySprite));
	MySprite->Init();

	SpriteNumber = SingleSpriteManeger.GetKey(L"BossMagic");
	MySprite = SingleSpriteManeger.GetSprite(SpriteNumber);
	MySprite->SetDrawTime(MyMagicMaxTime);
	MyStateList.insert(std::make_pair(Boss_Magic, MySprite));
	MySprite->Init();

	MyState = Boss_Spawn;
	MySprite = MyStateList.find(MyState)->second;

	MyHP = 100;

	POINT SubBoss1Point;
	SubBoss1Point.x = 200;
	SubBoss1Point.y = 600;
	bSubBoss1 = false;
	SubBoss1MaxTime = 6.0f;
	SubBoss1Time = 0;

	POINT SubBoss2Point;
	SubBoss2Point.x = 100;
	SubBoss2Point.y = 450;
	bSubBoss2 = false;
	SubBoss2MaxTime = 4.0f;
	SubBoss2Time = 0;

	MySssSubBoss1.Init(OffScreen, SubBoss1Point, WindowDC);
	MySssSubBoss2.Init(OffScreen, SubBoss2Point, WindowDC);
	
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
		bAttack = true;
	}
	if (bAttack && !bIdle)
	{
		bSummon = true;
		bAttack = false;
		if (rand() % 2 != 0)
		{
			bSubBoss1 = true;
			MySssSubBoss1.SetReady();
		}
		else
		{
			bSubBoss2 = true;
			MySssSubBoss2.SetReady();
		}

	}

	
	if(bSummon && MySummonTime < MySummonMaxTime)
	{
		MySummonTime += GetSecPerFrame;
		MyState = MyFsm.GetState(MyState, Boss_Summon);
	}
	else if(bSummon)
	{
		MyMagicTime = 0;
		MySummonTime = 0;
		bSummon = false;
		bMagic = false;
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

	if (bSubBoss1 && SubBoss1MaxTime > SubBoss1Time)
	{
		SubBoss1Time += GetSecPerFrame;
	}
	else if(bSubBoss1)
	{
		bSubBoss1 = false;
		SubBoss1Time = 0;
	}
	if (bSubBoss2 && SubBoss2MaxTime > SubBoss2Time)
	{
		SubBoss2Time += GetSecPerFrame;
	}
	else if (bSubBoss2)
	{
		bSubBoss2 = false;
		SubBoss2Time = 0;
	}

	if (bStop && MyStopTime < MyStopMaxTime)
	{
		MyStopTime += GetSecPerFrame;	
	}
	else if(bStop)
	{
		bStop = false;
		MyStopTime = 0;
		int Xpos = rand() % (2048 - 400) + 200;
		int Ypos = rand() % (768 - 380) + 190;
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

	if (MyHP <= 0)
	{
		MyState = MyFsm.GetState(MyState, Boss_Death);
		if (MyCollider != NULL)
		{
			CollisionManeger.DeleteColider(MyCollider);
			MyCollider = NULL;
			bDeath = true;
		}
	}
	else
	{
		MyCollider->SetPoint(MyPos);
		MySssSubBoss1.GetPlayerPoint(MyPlayer->GetPos());
		MySssSubBoss1.Frame();
		MySssSubBoss2.Frame();
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
	MySssSubBoss1.Render();
	MySssSubBoss2.Render();
	
	
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
	MySssSubBoss1.Release();
	MySssSubBoss2.Release();
	DeleteObject(SelectObject(MyScreen, MyOldBitMap));
	DeleteDC(MyScreen);

	return true;
}
bool SssMainBoss::CheckEvent(SssObject& TargetObject)
{
	if (TargetObject.GetName() == L"Player_Bullet")
	{
		if (MyState == Boss_Idle || MyState == Boss_Summon || MyState == Boss_Magic)
		{
			if (DamegeMaxTime <= DamegeTime)
			{
				MyHP -= 1;
				DamegeTime = 0;
			}
		}
	}
	return true;
}


SssMainBoss::SssMainBoss()
{
}


SssMainBoss::~SssMainBoss()
{
}
