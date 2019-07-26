#pragma once
#include "SssSceeen.h"
#include "SssTitleObject.h"

class SssTitle :public SssSceeen
{
public:
	std::list<SssTitleObject*> TitleObjectList;
	int iSoundIndex;
public:
	virtual bool Init(HDC WindowDC, HDC OffScreen);
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	SssTitle() {}
	~SssTitle() {}
};

