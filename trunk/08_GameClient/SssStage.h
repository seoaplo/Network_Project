#pragma once
#include "SssSceeen.h"
#include "SssPlayer.h"
#include "SssWall.h"
#include "SssMainBoss.h"

class SssStage : public SssSceeen
{
public:
	HDC MyScreen;
	HBITMAP MyScreenBitMap;
	HBITMAP OldBitMap;
	POINT CameraPoint;
	std::list<SssObject*> MyObjectList;
	float fReadyTime;
	float fReadyMaxTime;
	int iSoundIndex;
	bool bVictory;
	bool bLose;
	float VictoryTime;
	float VictoryMaxTime;
	float LoseTime;
	float LoseMaxTime;
public:
	virtual bool Init(HDC WindowDC, HDC OffScreen);
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	SssStage();
	~SssStage();
};

