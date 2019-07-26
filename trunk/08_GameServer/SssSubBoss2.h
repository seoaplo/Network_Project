#pragma once
#include "Ssslibheader.h"

class SssSubBoss2 : public SssObject
{
	HDC MyWindowDC;
	POINT PlayerPoint;
	
	SssImege* MyReadyImege;
	SssImege* MyReadyWeponImege;
	SssImege* MyAttackImege;
	SssImege* MyAttackWeponImege;

	COLORREF MyColor;
public:
	bool bAttackReady;
	float fAttackReadyTime;
	float fAttackReadyMaxTime;
public:
	bool bAttack;
	float fAttackTime;
	float fAttackMaxTime;
public:
	POINT MySpawnPos;
	SssPoint MyRealPos;
public:
	void SetReady()
	{
		MyPos = MySpawnPos;
		MyRealPos.x = MySpawnPos.x;
		MyRealPos.y = MySpawnPos.y;
		bAttackReady = true;
		SingleSoundManeger.PlayEffect(iSoundIndex);
	}
public:
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssSubBoss2();
	~SssSubBoss2();
};

