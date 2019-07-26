#pragma once

#include "SssSpriteManeger.h"
#include "SssSound.h"
#include "SssCollider.h"

class SssObject
{

public:
	POINT MyPos;
	SssSprite* SpriteImege;
	SssSprite* SpriteMask;
	SssCollider* MyCollider;
	int iSoundIndex;
	HDC MyScreen;
	HDC MyOffScreen;
	RECT MyRect;
	HBITMAP MyBitMap;
	HBITMAP MyOldBitMap;
	std::wstring ObjectName;
public:
	virtual bool Init(HDC OffScreen, POINT TargetPos, HDC WindowDC) { return true; }
	virtual bool Frame() { return true; }
	virtual bool Render() { return true; }
	virtual bool Release() { return true; }
	virtual bool CheckEvent(SssObject& TargetObject) { return true; }
public:
	POINT GetPos()
	{
		return MyPos;
	}
	RECT GetRect()
	{
		return MyRect;
	}
	std::wstring& GetName()
	{
		return ObjectName;
	}
public:
	SssObject() {}
	~SssObject() {}
};


