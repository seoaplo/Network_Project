#pragma once
#include "SssBullet.h"

class SssAttacker : public SssObject
{
public:
	SssImege* MyImege;
	//SssImege* MyMask;
	float MyDegree;
	COLORREF MyColor;
	float fBulletShootTime;
	float fBulletShootMaxTime;
	std::list<SssPlayerBullet*> BulletList;
	std::vector<SssPlayerBullet*> DeleteBulletList;
	float fBulletSpeed;
	float MyLength;
	HDC MyWindowDC;
public:
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
	bool SetPosition(POINT TargetPoint);
public:
	SssAttacker();
	~SssAttacker();
};

