#pragma once
#include "SServerStd.h"
#include "Protocol.h"
#include "Game/Ssslibheader.h"
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
	bool PacketProcess(PACKET pack);
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
	bool PacketProcess(PACKET pack);
public:
	SssWall();
	~SssWall();
};

