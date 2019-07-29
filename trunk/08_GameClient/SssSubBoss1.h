#pragma once
#include "Game/Ssslibheader.h"
#include "SssBullet.h"

class SssSubBoss1 : public SssObject
{
public:
	SssImege* MyImege;
	//SssImege* MyMask;
	float MyDegree;
	COLORREF MyColor;
	COLORREF MyColor2;
	float fBulletShootTime;
	float fBulletShootMaxTime;
	std::list<SssSubBoss1Bullet*> BulletList;
	std::vector<SssSubBoss1Bullet*> DeleteBulletList;
	SssSprite* EndSprite;
	float fBulletSpeed;
	float MyLength;
	HDC MyWindowDC;
	POINT PlayerPoint;
	POINT ShootPos;
public:
	bool bAttackReady;
	float fAttackReadyTime;
	float fAttackReadyMaxTime;
public:
	bool bAttack;
	float fAttackTime;
	float fAttackMaxTime;
public:
	bool bAttackEnd;
	float fAttackEndTime;
	float fAttackEndMaxTime;

public:
	void SetReady()
	{
		bAttackReady = true;
	}
public:
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
	void GetPlayerPoint(POINT point)
	{
		PlayerPoint = point;
	}
public:
	SssSubBoss1();
	~SssSubBoss1();
};

