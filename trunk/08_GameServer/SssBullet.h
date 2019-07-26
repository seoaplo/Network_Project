#pragma once
#include "Ssslibheader.h"
#include "SssEffect.h"

class SssBullet : public SssObject
{
public:
	float MyfSpeed;
	SssPoint MyDistance;
	SssPoint MyRealPos;
	float MyDegree;
	bool bDelete;
	bool bDeleteReady;
	float SssEffectTime;
	float SssEffectMaxTime;
	SssEffect MyEffect;
public:
	virtual bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, float fSpeed, SssPoint Distans, SssPoint RealPos, float TargetDgree);
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual bool CheckEvent(SssObject& TargetObject);
	virtual bool DeleteThis()
	{
		return bDelete;
	}
public:
	SssBullet();
	~SssBullet();
};

class SssPlayerBullet : public SssBullet
{

public:
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, float fSpeed, SssPoint Distans, SssPoint RealPos, float TargetDgree);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssPlayerBullet() {};
	~SssPlayerBullet() {};
};


class SssSubBoss1Bullet : public SssBullet
{

public:
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC, float fSpeed, SssPoint Distans, SssPoint RealPos, float TargetDgree);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	SssSubBoss1Bullet() {};
	~SssSubBoss1Bullet() {};
};
