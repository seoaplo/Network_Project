#pragma once
#include "Game/SssObject.h"
#include "SssBullet.h"
#include "SssFSM.h"
#include <time.h>
#include "SssSubBoss1.h"
#include "SssSubBoss2.h"

enum BossState
{
	Boss_Idle = 0,
	Boss_Spawn,
	Boss_Teleport1,
	Boss_Teleport2,
	Boss_Death,
	Boss_Summon,
	Boss_Magic,
	Boss_StateSize
};

enum BossEvent
{
	Boss_EventIdle = 0,
	Boss_EventSpawn,
	Boss_EventTeleport1,
	Boss_EventTeleport2,
	Boss_EventDeath,
	Boss_EventSummon,
	Boss_EventMagic,
	Boss_EventSize
};

class SssMainBoss : public SssObject
{
public:
	SssSprite* MySprite;
	std::map <DWORD, SssSprite*> MyStateList;
	COLORREF MyColor;
	SssFSM MyFsm;
	SssObject* MyPlayer;
	int MyState;
	int MybeforeState;
public:
	bool bStart;
	float MyStartTime;
	float MyStartMaxTime;
public:
	bool bIdle;
	float MyIdleTime;
	float MyidleMaxTime;
public:
	bool bAttack;
	bool bSummon;
	bool bMagic;
	float MySummonTime;
	float MySummonMaxTime;
	float MyMagicTime;
	float MyMagicMaxTime;
public:
	bool bTeleport1;
	bool bTeleport2;
	float MyTeleportTime1;
	float MyTeleportMaxTime1;
public:
	bool bStop;
	float MyStopTime;
	float MyStopMaxTime;
	float MyTeleportTime2;
	float MyTeleportMaxTime2;
public:
	int MyHP;
	float DamegeTime;
	float DamegeMaxTime;
public:
	bool bReady;
	bool bDeath;
	bool bLose;
public:
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	bool bSubBoss1;
	float SubBoss1MaxTime;
	float SubBoss1Time;
	SssSubBoss1 MySssSubBoss1;
public:
	bool bSubBoss2;
	float SubBoss2MaxTime;
	float SubBoss2Time;
	SssSubBoss2 MySssSubBoss2;
public:
	void GetPlayer(SssObject& Player)
	{
		MyPlayer = &Player;
	}
	void SetReady()
	{
		bReady = true;
	}
	bool GetDeath()
	{
		return bDeath;
	}
	void SetLose()
	{
		bLose = true;
	}
public:
	SssMainBoss();
	~SssMainBoss();
};

