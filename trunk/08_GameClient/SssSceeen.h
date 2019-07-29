#pragma once
#include "SServerStd.h"
#include "Protocol.h"
#include "Game/Ssslibheader.h"

enum Sceen
{
	SC_TITLE,
	SC_Stage,
	SC_ResultWin,
	SC_ResultLose
};

class SssSceeen
{
public:
	HDC MyWindowDC;
	HDC MyOffScreenDC;
	SssImege* MyBackGroundImege;
	POINT MyPoint;
	int iChangeSceen;
	std::list<SssObject> ObjectList;
public:
	virtual bool Init(HDC WindowDC, HDC OffScreen);
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	int GetSceenChanege()
	{
		return iChangeSceen;
	}
public:
	SssSceeen();
	~SssSceeen();
};
