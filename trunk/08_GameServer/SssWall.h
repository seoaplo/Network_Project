#pragma once
#include "Ssslibheader.h"


class SssGround :public SssObject
{
public:
	SssImege* MyImege;
public:
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
	bool CreateRect() { return true; }
public:
	SssGround();
	~SssGround();
};

class SssWall :public SssObject
{
public:
	SssImege* MyImege;
public:
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
	bool CreateRect() { return true; }
public:
	SssWall();
	~SssWall();
};

