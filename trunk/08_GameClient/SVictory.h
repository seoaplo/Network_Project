#pragma once
#include "SServerStd.h"
#include "Protocol.h"
#include "Game/Ssslibheader.h"

class SVictory : public SssObject
{
public:
	SssImege* MyImege;
	COLORREF MyColor;
public:
	bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC);
	bool Frame();
	bool Render();
	bool Release();
	bool CheckEvent(SssObject& TargetObject);
public:
	virtual bool PacketProcess(PACKET pack);
public:
	SVictory();
	~SVictory();
};

